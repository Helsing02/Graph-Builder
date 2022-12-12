#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "FuncCollection.h"


namespace Ui {
class FuncWindow;
}

class FuncWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FuncWindow(QWidget *parent = nullptr);
    ~FuncWindow();
    int add_func(std::string);
    void add_graphs(int, int);
    void change_size(int, int, int, int);

private slots:
    void rebuild();


private:
    Ui::FuncWindow *ui;
    QCustomPlot *wGraphic;
};

#endif // FUNCWINDOW_H
