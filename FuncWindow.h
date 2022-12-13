#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "FuncCollection.h"

namespace Ui
{
class FuncWindow;
}

class FuncWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit FuncWindow(QWidget *parent = nullptr);
    ~FuncWindow();
    int add_func(std::string new_func);
    void add_graphs(double x_min, double x_max);
    void change_size(int, int, int, int);

private slots:
    void rebuild(QCPRange,QCPRange);

/*
private slots:
    void on_pushButton_clicked();
*/
private:
    Ui::FuncWindow *ui;
    QCustomPlot *w_graphic;
    FuncCollection m_func_collection;
};

#endif // FUNCWINDOW_H
