#include "renderarea.h"
#include "window.h"

#include <QtWidgets>
#include <QGridLayout>

const int IdRole = Qt::UserRole;

Window::Window()
{
    renderArea = new RenderArea;

    //tension spinbox
    tensionSpinBox = new QSpinBox;
    tensionSpinBox->setRange(0, 9);
    tensionSpinBox->setPrefix("0.");

    tensionLabel = new QLabel(tr("Tension[0,1]:"));
    tensionLabel->setBuddy(tensionSpinBox);

    //grain spinbox
    grainSpinBox=new QSpinBox;
    grainSpinBox->setRange(10, 50);
    grainLabel = new QLabel(tr("Grain[10,50]:"));
    grainLabel->setBuddy(grainSpinBox);

    //speed slider
    speedSlider=new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(3);
    speedSlider->setMaximum(10);
    speedLabel= new QLabel(tr("Speed"));
    speedLabel->setBuddy(speedSlider);

    //showPoints button
    showPointsButton=new QPushButton(tr("Show Points"));

    //drawLine button
    drawLineButton = new QPushButton(tr("Draw Line"));

    //clear button
    clearButton = new QPushButton(tr("Clear"));\

    //play button
    playButton = new QPushButton(tr("Play"));


    connect(tensionSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(tensionChanged(int)));
    connect(grainSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(grainChanged(int)));
    connect(speedSlider, SIGNAL(valueChanged(int)),
            this, SLOT(speedChanged(int)));

    connect(showPointsButton, SIGNAL(clicked()),
            this, SLOT(showSplinePoints()));
    connect(drawLineButton, SIGNAL(clicked()),
            this, SLOT(drawLine()));
    connect(clearButton, SIGNAL(clicked()),
            this, SLOT(clear()));
    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setRowStretch(0,renderArea->height);
    mainLayout->setColumnStretch(0, 1);
    //Columns with a higher stretch factor take more of the available space.
    //default is 0
    mainLayout->setColumnStretch(3, 1);
    resize(500,500);
    mainLayout->addWidget(renderArea, 0, 0, renderArea->height, renderArea->width);

    mainLayout->addWidget(tensionLabel, 1, 0, Qt::AlignRight);
    mainLayout->addWidget(tensionSpinBox, 1, 1);
    mainLayout->addWidget(grainLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(grainSpinBox, 2, 1);

    mainLayout->addWidget(showPointsButton, 1, 3);
    mainLayout->addWidget(drawLineButton, 2, 3);
    mainLayout->addWidget(clearButton, 3, 3);

    mainLayout->addWidget(speedLabel, 1, 4, Qt::AlignRight);
    mainLayout->addWidget(speedSlider, 1, 5);
    mainLayout->addWidget(playButton, 2, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("E1"));
}

void Window::tensionChanged(int value){
    renderArea->setTension(float(value)*0.1f);
}
void Window::grainChanged(int value){
    renderArea->setGrain(value);
}
void Window::speedChanged(int value){
    renderArea->setSpeed((float)value*0.001);
}

void Window::showSplinePoints(){
    renderArea->showPoints();
}
void Window::drawLine(){
    renderArea->drawLine();
}
void Window::clear(){
    renderArea->clear();
}
void Window::play(){
    renderArea->play();
}
