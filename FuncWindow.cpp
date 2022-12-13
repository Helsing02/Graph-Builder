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
    ui->horizontalLayout_2->addWidget(w_graphic);
    w_graphic->xAxis->setLabel("x");
    w_graphic->yAxis->setLabel("y");
    w_graphic->setInteraction(QCP::iRangeDrag, true);
    w_graphic->setInteraction(QCP::iRangeZoom, true);

    connect(w_graphic->xAxis, SIGNAL(rangeChanged(QCPRange, QCPRange)), this, SLOT(rebuild(QCPRange, QCPRange)));
}

FuncWindow::~FuncWindow()
{
    delete ui;
}

void FuncWindow::change_size(int x_min, int x_max, int y_min, int y_max)
{
    w_graphic->xAxis->setRange(x_min, x_max);
    w_graphic->yAxis->setRange(y_min, y_max);
}

void FuncWindow::add_graphs(double x_min, double x_max)
{
    QVector<QVector<QVector<double>>> graphs;
    graphs = m_func_collection.get_points(x_min, x_max);

    int index = 0;
    for(QVector<QVector<double>> m_graph: graphs)
    {
        w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
        index++;
    }
}

int FuncWindow::add_func(std::string new_func)
{
    w_graphic->addGraph(w_graphic->xAxis, w_graphic->yAxis);
    return m_func_collection.add_func(new_func);
}

void FuncWindow::rebuild(QCPRange new_range, QCPRange old_range)
{
    std::cout<<old_range.lower<<" "<<old_range.upper<<" "<<new_range.lower<<" "<<new_range.upper<<std::endl;
    if((new_range.upper-new_range.lower)!=(old_range.upper-old_range.lower)){
        std::cout<<"change size\n";
        add_graphs(new_range.lower, new_range.upper);
        w_graphic->replot();
    } else {
        std::cout<<"grab\n";
        if(new_range.lower<old_range.lower){
            QVector<QVector<QVector<double>>> graphs;
            graphs = m_func_collection.get_points(new_range.lower, new_range.upper);

            int index = 0;
            for(QVector<QVector<double>> m_graph: graphs)
            {
                w_graphic->graph(index)->setData(m_graph[0], m_graph[1]);
                index++;
            }
        } else {

        }
        if(new_range.upper>old_range.upper){
            add_graphs(old_range.upper, new_range.upper);
        } else {

        }
        w_graphic->replot();
    }


}
