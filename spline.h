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
    int totalPointCount;
    float speed;

private:

    //static Spline* newSpline;
    float CardinalMatrix(int i, std::string coordinate, float u);
    void addEndingPoints(std::vector<QPoint> &points);
    void interpolateBetween2Points(int starti);
    void initInterpolationParameters(std::vector<QPoint> &points);
    void calculateTangentValues();
    float t;//tension
    float m[16];
    float *Ax, *Bx,*Cx,*Dx,*Ay,*By,*Cy,*Dy;
};

#endif // SPLINE_H
