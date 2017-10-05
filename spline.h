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
    float CardinalMatrix(float a, float b, float c, float d, float u);
    void addEndingPoints(std::vector<QPoint> &points);
    void interpolateBetween2Points(std::vector<QPoint> &points, int starti, int endi);
    float t;//tension
    float m[16];
};

#endif // SPLINE_H
