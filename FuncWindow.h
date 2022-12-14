#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QString>
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
    int add_func(QString new_func, QColor col);
    void add_graphs(double x_min, double x_max);
    void set_range_pi(double, double);
    void find_range_y();
    void change_range_x(double, double);
    void change_range_y(double, double);

private slots:
    void save_pic();
    void rebuild(QCPRange);

private:
    Ui::FuncWindow *ui;
    QCustomPlot *w_graphic;
    FuncCollection m_func_collection;
    double x_old_min;
    double x_old_max;
    double y_att_x;
    double y_old_min;
};

#endif // FUNCWINDOW_H
