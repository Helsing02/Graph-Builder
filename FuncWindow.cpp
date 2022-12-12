#include "FuncWindow.h"
#include "ui_funcwindow.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <QString>

FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::FuncWindow)
{
    ui->setupUi(this);

    wGraphic = new QCustomPlot();
    ui->horizontalLayout_2->addWidget(wGraphic);
    this->setStyleSheet("background-color:rgb(255,255,255);");
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

//    wGraphic->setBackground(QBrush(QColor("#dcb9ff")));

    wGraphic->replot();


    wGraphic->setInteraction(QCP::iRangeZoom, true);
    wGraphic->setInteraction(QCP::iRangeDrag, true);
}

void FuncWindow::clearGraphs(){
    wGraphic->clearGraphs();
}

void FuncWindow::replot(){
    wGraphic->replot();

    wGraphic->setInteraction(QCP::iRangeZoom, true);
    wGraphic->setInteraction(QCP::iRangeDrag, true);
}



void FuncWindow::on_pushButton_clicked()
{
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                   initialPath,
                                   tr("%1 Files (*.%2);;All Files (*)")
                                   .arg(format.toUpper())
                                   .arg(format));
    wGraphic->savePng(fileName);
}

