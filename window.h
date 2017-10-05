#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <stdio.h>

class QLabel;
class QPushButton;
class QSpinBox;
class QSlider;

class RenderArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private slots:

    void tensionChanged(int value);
    void grainChanged(int value);
    void speedChanged(int value);

    void showSplinePoints();
    void drawLine();
    void clear();
    void play();

private:
    RenderArea *renderArea;

    //tension spinbox
    QLabel *tensionLabel;
    QSpinBox *tensionSpinBox;
    //grain spinbox
    QLabel *grainLabel;
    QSpinBox *grainSpinBox;
    //speed slider
    QLabel *speedLabel;
    QSlider *speedSlider;
    //showPoints button
    QPushButton *showPointsButton;
    //drawLine button
    QPushButton *drawLineButton;
    //clear button
    QPushButton *clearButton;
    //play button
    QPushButton *playButton;

};

#endif // WINDOW_H
