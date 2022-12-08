#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class FuncWindow;
}

class FuncWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FuncWindow(QWidget *parent = nullptr);
    ~FuncWindow();
    void addGraph(QVector <double>, QVector <double>, int);
    void changeSize(int, int, int, int);
    void replot();
    void clearGraphs();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FuncWindow *ui;
    QCustomPlot *wGraphic;
};

#endif // FUNCWINDOW_H
