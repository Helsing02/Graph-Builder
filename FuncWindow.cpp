#include "FuncWindow.h"
#include "ui_funcwindow.h"

FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::FuncWindow)
{
    ui->setupUi(this);

    wGraphic = new QCustomPlot();
    ui->gridLayout->addWidget(wGraphic);


}

FuncWindow::~FuncWindow()
{
    delete ui;
}

void FuncWindow::changeSize(int xMin, int xMax, int yMin, int yMax)
{
    wGraphic->xAxis->setRange(xMin, xMax);
    wGraphic->yAxis->setRange(yMin, yMax);
}

void FuncWindow::addGraph(QVector <double> x, QVector <double> y, int index)
{
    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(index)->setData(x, y);
    wGraphic->replot();
}

void FuncWindow::clearGraphs(){
    wGraphic->clearGraphs();
}

void FuncWindow::replot(){
    wGraphic->replot();
}

