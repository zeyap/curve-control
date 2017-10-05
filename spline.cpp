#include "spline.h"

Spline::Spline()
{
    grain=10;
    speed=0.003f;//bydefault
    t=0.5f;
    isEndingPointsAdded=false;
}
void Spline::clearPrevIntPoints(){
    intPoints.clear();
    pTangent.clear();
}

float Spline::CardinalMatrix(float a, float b, float c, float d, float u){
    float p0, p1 ,p2 ,p3;
    p0=m[0]*a+m[1]*b+m[2]*c+m[3]*d;
    p1=m[4]*a+m[5]*b+m[6]*c+m[7]*d;
    p2=m[8]*a+m[9]*b+m[10]*c+m[11]*d;
    p3=m[12]*a+m[13]*b+m[14]*c+m[15]*d;
    return(p3+u*(p2+u*(p1+u*p0)));
}

void Spline::addInterpolativePoints(std::vector<QPoint> &points){
    if(points.size()>=4){
        addEndingPoints(points);
        for(int i=0;i<points.size();i+=1){
            if(i+3<points.size()){
                interpolateBetween2Points(points,i+1,i+2);
            }
        }

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

void Spline::interpolateBetween2Points(std::vector<QPoint> &points,int starti, int endi){
    float ustep=1.0f/(grain+1);
    float u=0;
    for(int count=0;count<grain;count++){
        QPoint* newp=new QPoint(CardinalMatrix(points[starti-1].x(),points[starti].x(),points[endi].x(),points[endi+1].x(),u),
                CardinalMatrix(points[starti-1].y(),points[starti].y(),points[endi].y(),points[endi+1].y(),u));
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



