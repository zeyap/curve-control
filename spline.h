#ifndef SPLINE_H
#define SPLINE_H

#include<QWidget>
#include <QPoint>;
#include <vector>;
#include <string>;
#include <stdio.h>;

class Spline
{
public:
    Spline();
    void addInterpolativePoints(std::vector<QPoint> &points);
    void updateParameters(float tension,int intplPointCount);
    void clearPrevIntPoints();
    std::vector<QPoint> intPoints;
    std::vector<float> pTangent;
    bool isEndingPointsAdded;
    int grain;
    float speed;

private:

    //static Spline* newSpline;
    float CardinalMatrix(int i, std::string coordinate, float u);
    void addEndingPoints(std::vector<QPoint> &points);
    QPoint interpolateOnCurve(int starti, float u);
    void initInterpolationParameters(std::vector<QPoint> &points);
    void calculateTangentValues();
    float calculateLen(int curvei);
    float calculateU(int i, float len);
    int calculateCurveSectioni(float len);
    float f(int curvei,float u);
    float simpsons(int curvei,float startu, float endu);
    float t;//tension
    float m[16];
    float *Ax, *Bx,*Cx,*Dx,*Ay,*By,*Cy,*Dy;
    float *A, *B, *C, *D, *E;
    float *curveLen;
    float totalCurveLen;
    int totalPointCount;
    float avgPointsDist;
    int curveSectionNum;
};

#endif // SPLINE_H
