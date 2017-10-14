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

    QLabel *tensionLabel;
    QSpinBox *tensionSpinBox;

    QLabel *grainLabel;
    QSpinBox *grainSpinBox;

    QLabel *speedLabel;
    QSlider *speedSlider;

    QPushButton *showPointsButton;

    QPushButton *drawLineButton;

    QPushButton *clearButton;

    QPushButton *playButton;

};

#endif // WINDOW_H
