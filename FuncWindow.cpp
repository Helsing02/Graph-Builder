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

    w_graphic = new QCustomPlot();
    ui->gridLayout->addWidget(w_graphic);
    w_graphic->setInteraction(QCP::iRangeDrag, true);
    w_graphic->setInteraction(QCP::iRangeZoom, true);
}

FuncWindow::~FuncWindow()
{
    delete ui;
}

void FuncWindow::change_size(int x_min, int x_max, int y_min, int y_max)
{
    w_graphic->xAxis->setRange(x_min, x_max);
    w_graphic->yAxis->setRange(y_min, y_max);

    cur_max_x = x_max;
    cur_min_x = x_min;
}

void FuncWindow::add_graphs(int x_min, int x_max)
{
    QVector<QVector<QVector<double>>> graphs;
    graphs = m_func_collection.get_points(x_min, x_max);

    w_graphic->xAxis->setLabel("x");
    w_graphic->yAxis->setLabel("y");

    for(QVector<QVector<double>> m_graph: graphs)
    {
        int index = 0;

        w_graphic->addGraph(w_graphic->xAxis, w_graphic->yAxis);
        w_graphic->graph(index)->setData(m_graph[0], m_graph[1]);
    }

    w_graphic->replot();
}

int FuncWindow::add_func(std::string new_func)
{
    return m_func_collection.add_func(new_func);
}

void FuncWindow::rebuild()
{
    int start_p, end_p;
    if((int)w_graphic->xAxis->range().upper > cur_max_x)
    {
        start_p = cur_max_x;
        end_p = (int)w_graphic->xAxis->range().upper;
    }
    else
    {
        start_p = cur_min_x;
        end_p = (int)w_graphic->xAxis->range().lower;
    }

    this->add_graphs(start_p, end_p);
    w_graphic->replot();
}
