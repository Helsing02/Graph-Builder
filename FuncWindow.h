#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

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
    void add_graphs(int x_min, int x_max);
    void change_size(int, int, int, int);
private:

    Ui::FuncWindow *ui;
    QCustomPlot *w_graphic;
    void rebuild();
};

#endif // FUNCWINDOW_H
