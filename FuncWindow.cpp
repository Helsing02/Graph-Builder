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
    w_graphic->setPlottingHint(QCP::phFastPolylines, true);

    setAttribute(Qt::WA_DeleteOnClose);

    w_graphic->legend = new QCPLegend;

    w_graphic->axisRect()->insetLayout()->addElement(w_graphic->legend, Qt::AlignTop|Qt::AlignRight);
    w_graphic->legend->setLayer("legend");

    connect(w_graphic->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(rebuild(QCPRange)));

    x_old_min = 0;
    x_old_max = 5;
    y_old_min = 0;
    y_old_max = 5;

    setWindowTitle("GraphicsBuilder");
}

FuncWindow::~FuncWindow()
{
    delete ui;
}

int FuncWindow::add_func(QString new_func, QColor col)
{
    w_graphic->addGraph(w_graphic->xAxis, w_graphic->yAxis);

    int m_count = w_graphic->graphCount();
    w_graphic->graph(m_count - 1)->setName(new_func);
    QPen pen;
    pen.setColor(col);
    pen.setWidth(1);
    w_graphic->graph(m_count - 1)->setPen(pen);
    w_graphic->graph(m_count-1)->addToLegend(w_graphic->legend);

    return m_func_collection.add_func(new_func.toStdString());
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

void FuncWindow::set_range_pi(double x_min, double x_max)
{
    double pi_min = x_min * 3.1415926535;
    double pi_max = x_max * 3.1415926535;
    QSharedPointer<QCPAxisTickerPi> pi_ticker(new QCPAxisTickerPi);

    w_graphic->xAxis->setRange(pi_min, pi_max);
    w_graphic->xAxis->setTicker(pi_ticker);
    x_old_min = pi_min;
    x_old_max = pi_max;
}

void FuncWindow::find_range_y()
{
    QVector<QVector<QVector<double>>> graphs;

    graphs = m_func_collection.get_points(x_old_min, x_old_max);

    double y_min = INFINITY;
    double y_max = -INFINITY;

    for(QVector<QVector<double>> m_graph: graphs)
    {
        for(double y: m_graph[1])
        {
            if(y_min > y) y_min = y;
            if(y_max < y) y_max = y;
        }
    }

    if(y_max > 100) y_max = 100;
    if(y_min < -100) y_min = -100;
    w_graphic->yAxis->setRange(y_min, y_max);

    y_old_min = y_min;
    y_old_max = y_max;
}

void FuncWindow::change_range_x(double x_min, double x_max)
{
    w_graphic->xAxis->setRange(x_min, x_max);
    x_old_min = x_min;
    x_old_max = x_max;
}

void FuncWindow::change_range_y(double y_min, double y_max)
{
    w_graphic->yAxis->setRange(y_min, y_max);
    y_old_min = y_min;
    y_old_max = y_max;
}

void FuncWindow::rebuild(QCPRange new_range)
{
    if(new_range.upper - new_range.lower > 300)
    {
        w_graphic->xAxis->setRange(x_old_min, x_old_max);
        w_graphic->yAxis->setRange(y_old_min, y_old_max);
        std::cout << "Stoped\n";
    }
    else
    {
        std::cout << y_old_min << " " << y_old_max << std::endl;

        double m_zoom_coef = (new_range.upper - new_range.lower)/(x_old_max - x_old_min);
        std::cout<<x_old_min<<" "<<x_old_max<<" "<<new_range.lower<<" "<<new_range.upper<<std::endl;

        double m_dif = (w_graphic->yAxis->range().upper - w_graphic->yAxis->range().lower) - (y_old_max - y_old_min);
        y_old_min = w_graphic->yAxis->range().lower + m_dif;
        y_old_max = w_graphic->yAxis->range().upper - m_dif;
        if(abs(new_range.lower - x_old_min) > (new_range.upper - new_range.lower)/100 &&
                abs(new_range.upper - x_old_max) > (new_range.upper - new_range.lower)/100)
        {
            if((new_range.upper-new_range.lower)!=(x_old_max-x_old_min)){
                std::cout<<"change size\n";

                QVector<QVector<QVector<double>>> graphs;
                graphs = m_func_collection.get_points(new_range.lower, new_range.upper, m_zoom_coef);

                int index = 0;
                for(QVector<QVector<double>> m_graph: graphs)
                {
                    w_graphic->graph(index)->setData(m_graph[0], m_graph[1]);
                    index++;
                }

                //y_old_min = w_graphic->yAxis->range().lower;
                //y_old_max = w_graphic->yAxis->range().upper;
                /*if(new_range.lower < x_old_min)
                {
                    QVector<QVector<QVector<double>>> graphs;
                    double m_div_points = abs(new_range.upper - x_old_max)/(x_old_max - x_old_min);
                    graphs = m_func_collection.get_points(new_range.lower, x_old_min, m_div_points);

                    int index = 0;
                    for(QVector<QVector<double>> m_graph: graphs)
                    {
                        w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                        index++;
                    }

                    graphs.clear();
                    graphs = m_func_collection.get_points(x_old_max, new_range.upper, m_div_points);

                    index = 0;
                    for(QVector<QVector<double>> m_graph: graphs)
                    {
                        w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                        index++;
                    }
                }*/
            } else {
                std::cout<<"grab\n";
                if(new_range.lower < x_old_min){

                    QVector<QVector<QVector<double>>> graphs;
                    double m_div_points = abs(new_range.upper - x_old_max)/(x_old_max - x_old_min);
                    graphs = m_func_collection.get_points(new_range.lower - (new_range.upper - new_range.lower)/40, x_old_min, m_div_points * m_zoom_coef);

                    int index = 0;
                    for(QVector<QVector<double>> m_graph: graphs)
                    {
                        w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                        w_graphic->graph(index)->data()->removeAfter(new_range.upper);
                        index++;
                    }
                } else {
                    QVector<QVector<QVector<double>>> graphs;
                    double m_div_points = abs(new_range.upper - x_old_max)/(x_old_max - x_old_min);
                    graphs = m_func_collection.get_points(x_old_max, new_range.upper + (new_range.upper - new_range.lower)/40, m_div_points * m_zoom_coef);

                    int index = 0;
                    for(QVector<QVector<double>> m_graph: graphs)
                    {
                        w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                        w_graphic->graph(index)->data()->removeBefore(new_range.lower);
                        index++;
                    }
                }

            }
            w_graphic->replot();
            x_old_min = new_range.lower;
            x_old_max = new_range.upper;
        }
    }
}

void FuncWindow::save_pic()
{
    QString format = "png";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                   initialPath,
                                   tr("%1 Files (*.%2);;All Files (*)")
                                   .arg(format.toUpper())
                                   .arg(format));
    w_graphic->savePng(fileName);
}
