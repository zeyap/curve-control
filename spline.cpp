#include "spline.h"

Spline::Spline()
{
    grain=10;
    speed=0.003f;//bydefault
    totalPointCount=0;
    t=0.5f;
    isEndingPointsAdded=false;
}
void Spline::clearPrevIntPoints(){
    intPoints.clear();
    pTangent.clear();
}

float Spline::CardinalMatrix(int i, std::string coordinate, float u){
    if(coordinate=="x"){
       return(Dx[i]+u*(Cx[i]+u*(Bx[i]+u*Ax[i])));
    }else{
       return(Dy[i]+u*(Cy[i]+u*(By[i]+u*Ay[i])));
    }

}

void Spline::initInterpolationParameters(std::vector<QPoint> &points){
    Ax=new float[points.size()];
    Bx=new float[points.size()];
    Cx=new float[points.size()];
    Dx=new float[points.size()];

    Ay=new float[points.size()];
    By=new float[points.size()];
    Cy=new float[points.size()];
    Dy=new float[points.size()];

    for(int i=0;i<points.size();i+=1){
        if(i+3<points.size()){
            int* x=new int[4]{points[i].x(),points[i+1].x(),points[i+2].x(),points[i+3].x()};
            int* y=new int[4]{points[i].y(),points[i+1].y(),points[i+2].y(),points[i+3].y()};

            Ax[i]=m[0]*x[0]+m[1]*x[1]+m[2]*x[2]+m[3]*x[3];
            Bx[i]=m[4]*x[0]+m[5]*x[1]+m[6]*x[2]+m[7]*x[3];
            Cx[i]=m[8]*x[0]+m[9]*x[1]+m[10]*x[2]+m[11]*x[3];
            Dx[i]=m[12]*x[0]+m[13]*x[1]+m[14]*x[2]+m[15]*x[3];

            Ay[i]=m[0]*y[0]+m[1]*y[1]+m[2]*y[2]+m[3]*y[3];
            By[i]=m[4]*y[0]+m[5]*y[1]+m[6]*y[2]+m[7]*y[3];
            Cy[i]=m[8]*y[0]+m[9]*y[1]+m[10]*y[2]+m[11]*y[3];
            Dy[i]=m[12]*y[0]+m[13]*y[1]+m[14]*y[2]+m[15]*y[3];
            delete x,y;
        }
    }
}

void Spline::calculateTangentValues(){
    for(int i=0;i<intPoints.size();i++){
        double tangent;
        float rot;//in degree counterclockwise
        if(i>=1&&i<intPoints.size()-1){
            if(intPoints[i+1].x()-intPoints[i-1].x()==0){
                if(intPoints[i+1].y()-intPoints[i-1].y()<0){//y从上往下递增
                    rot=90.0f;
                }
                else if(intPoints[i+1].y()-intPoints[i-1].y()>0){
                    rot=-90.0f;
                }
                else{
                    rot=pTangent[i-1];
                }
            }else{
                tangent=(double)(-intPoints[i+1].y()+intPoints[i-1].y())/(double)(intPoints[i+1].x()-intPoints[i-1].x());
                rot=180/3.14f*(float)atan(tangent);
            }
        }else if(i==0){
            rot=0;
        }else{
            rot=pTangent[i-1];
        }
        //printf("%f ",rot);
        pTangent.push_back(-rot);
    }
}

void Spline::addInterpolativePoints(std::vector<QPoint> &points){
    if(points.size()>=4){
        addEndingPoints(points);
        initInterpolationParameters(points);

        for(int i=0;i<points.size();i+=1){
            if(i+3<points.size()){
                interpolateBetween2Points(i+1);
            }
        }

        calculateTangentValues();
    }
}

void Spline::addEndingPoints(std::vector<QPoint> &points){
    if(isEndingPointsAdded==false){
        QPoint* temp=new QPoint(points[0].x(),points[0].y());
        std::vector<QPoint>::iterator it=points.begin();
        points.insert(it,temp[0]);
        delete temp;

        temp=new QPoint(points[points.size()-1].x(),points[points.size()-1].y());
        it=points.end();
        points.insert(it,temp[0]);
        delete temp;

        isEndingPointsAdded=true;
    }
}

void Spline::interpolateBetween2Points(int starti){
    float ustep=1.0f/(grain+1);
    float u=0;
    for(int count=0;count<grain;count++){
        QPoint* newp=new QPoint(CardinalMatrix(starti-1,"x",u),CardinalMatrix(starti-1,"y",u));
        intPoints.push_back(newp[0]);
        u+=ustep;
    }
}



void Spline::updateParameters(float tension,int intplPointCount){
    if(tension>0){
        t=tension;
        float temp[]={-t,2-t,-2+t,t, 2*t,-3+t,3-2*t,-t, -t,0,t,0, 0,1,0,0};
        for(int i=0;i<16;i++){
            m[i]=temp[i];
        }
    }
    if(intplPointCount>0){
        grain=intplPointCount;

    }
}



