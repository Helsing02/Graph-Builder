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
    void add_graphs(int x_min, int x_max);
    void change_size(int, int, int, int);

private slots:
    void rebuild();


private:
    Ui::FuncWindow *ui;
    QCustomPlot *w_graphic;
    FuncCollection m_func_collection;
    int cur_min_x;
    int cur_max_x;
    void rebuild();
};

#endif // FUNCWINDOW_H
