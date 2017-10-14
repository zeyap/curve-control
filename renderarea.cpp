#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    splineControl=new(Spline);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    pointsDrawn=false;
    mode=points;
    movingStep=0;
    isAvatarShown=false;

    isTimerEnabled=false;
}

void RenderArea::setTension(float value){
    splineControl->updateParameters(value,-1);
}
void RenderArea::setGrain(int value){
    splineControl->updateParameters(-1,value);
}
void RenderArea::setSpeed(float value){
    splineControl->speed=value;
    if(isTimerEnabled){
        delete timer;
    }

    timer = new QTimer(this);
    isTimerEnabled=true;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5/(splineControl->speed*splineControl->grain));

}
void RenderArea::showPoints(){
    redrawIntPoints();
    pointsDrawn=true;
    mode =points;
    update();
}

void RenderArea::drawLine(){
    redrawIntPoints();
    pointsDrawn=true;
    mode =line;
    update();
}

void RenderArea::redrawIntPoints(){
    splineControl->clearPrevIntPoints();
    splineControl->addInterpolativePoints(pointsCoord);
}

void RenderArea::clear(){
    isAvatarShown=false;
    pointsDrawn=false;
    pointsCoord.clear();
    splineControl->clearPrevIntPoints();
    splineControl->isEndingPointsAdded=false;
    update();
}

void RenderArea::play(){

    isAvatarShown=true;
    avatar.load(":\\image\\motorcycle.png");
    setSpeed(splineControl->speed);

    update();

}

void RenderArea::mousePressEvent(QMouseEvent *event){

    if(pointsDrawn==true){
        clear();
    }
    float x = event->pos().x();
    float y=event->pos().y();
    pointsCoord.push_back(QPoint((int)x,(int)y));
    update();

}

void RenderArea::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QColor cPoint=QColor(0,0,0);
    painter.setPen(QPen(cPoint,0));

    for(int i=0;i<pointsCoord.size();i++){
        painter.drawEllipse(pointsCoord[i],5,5);
    }

    if(mode==line){
        QPainterPath path;
        for(int i=0;i<splineControl->intPoints.size();i++){
            if(i==0){
                path.moveTo(splineControl->intPoints[i].x(),splineControl->intPoints[i].y());
            }else{
                path.lineTo(splineControl->intPoints[i].x(),splineControl->intPoints[i].y());
            }
        }
        painter.drawPath(path);
    }
    else{
        painter.save();
        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
        for(int i=0;i<splineControl->intPoints.size();i++){
            painter.drawEllipse(splineControl->intPoints[i],3,3);

        }
        painter.restore();
    }

    if(isAvatarShown){
        if(movingStep<splineControl->intPoints.size()){

            QTransform trans;
            QPoint rotCenter=splineControl->intPoints[movingStep];
            trans.translate(rotCenter.x(),rotCenter.y());
            trans.rotate(splineControl->pTangent[movingStep]);
            trans.translate(-rotCenter.x(),-rotCenter.y());
            painter.setWorldTransform(trans);

            painter.drawPixmap(splineControl->intPoints[movingStep].x(),splineControl->intPoints[movingStep].y(),avatar);
            movingStep++;
        }else{
            movingStep=0;
        }
    }

}
