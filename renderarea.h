#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include<QImage>
#include<QLabel>
#include<QTimer>

#include <vector>
#include<string>
#include<spline.h>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    Spline* splineControl;
    RenderArea(QWidget *parent = 0);
    int height=100;
    int width=100;
    std::vector<QPoint> pointsCoord;
    enum drawMode {points, line} mode;

public slots:
    void setTension(float value);
    void setGrain(int value);
    void setSpeed(float value);

    void showPoints();
    void drawLine();
    void clear();
    void play();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void redrawIntPoints();

private:
    bool pointsDrawn;
    bool isAvatarShown;

    QPixmap avatar;
    int movingStep;
    QTimer *timer;
    bool isTimerEnabled;

};

#endif // RENDERAREA_H
