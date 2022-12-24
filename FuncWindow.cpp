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


    setAttribute(Qt::WA_DeleteOnClose);

    w_graphic->legend = new QCPLegend;

    w_graphic->axisRect()->insetLayout()->addElement(w_graphic->legend, Qt::AlignTop|Qt::AlignRight);
    w_graphic->legend->setLayer("legend");

    connect(w_graphic->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(rebuild(QCPRange)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(save_pic()));
    old_min = 0;
    old_max = 5;

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
    old_min = pi_min;
    old_max = pi_max;
}

void FuncWindow::find_range_y()
{
    QVector<QVector<QVector<double>>> graphs;

    graphs = m_func_collection.get_points(old_min, old_max);

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

    w_graphic->yAxis->setRange(y_min, y_max);
}

void FuncWindow::change_range_x(double x_min, double x_max)
{
    w_graphic->xAxis->setRange(x_min, x_max);
    old_min = x_min;
    old_max = x_max;
}

void FuncWindow::change_range_y(double y_min, double y_max)
{
    w_graphic->yAxis->setRange(y_min, y_max);
}

void FuncWindow::rebuild(QCPRange new_range)
{
    std::cout<<old_min<<" "<<old_max<<" "<<new_range.lower<<" "<<new_range.upper<<std::endl;
    if(abs(new_range.lower - old_min) > (new_range.upper - new_range.lower)/100 &&
            abs(new_range.upper - old_max) > (new_range.upper - new_range.lower)/100)
    {
        if((new_range.upper-new_range.lower)!=(old_max-old_min)){
            std::cout<<"change size\n";
            if(new_range.lower < old_min)
            {
                QVector<QVector<QVector<double>>> graphs;
                double m_div_points = abs(new_range.upper - old_max)/(old_max - old_min);
                graphs = m_func_collection.get_points(new_range.lower, old_min, m_div_points);

                int index = 0;
                for(QVector<QVector<double>> m_graph: graphs)
                {
                    w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                    index++;
                }

                graphs.clear();
                graphs = m_func_collection.get_points(old_max, new_range.upper, m_div_points);

                index = 0;
                for(QVector<QVector<double>> m_graph: graphs)
                {
                    w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                    index++;
                }
            }
        } else {
            std::cout<<"grab\n";
            if(new_range.lower < old_min){

                QVector<QVector<QVector<double>>> graphs;
                double m_div_points = abs(new_range.upper - old_max)/(old_max - old_min);
                graphs = m_func_collection.get_points(new_range.lower - (new_range.upper - new_range.lower)/40, old_min, m_div_points);

                int index = 0;
                for(QVector<QVector<double>> m_graph: graphs)
                {
                    w_graphic->graph(index)->addData(m_graph[0], m_graph[1]);
                    w_graphic->graph(index)->data()->removeAfter(new_range.upper);
                    index++;
                }
            } else {
                QVector<QVector<QVector<double>>> graphs;
                double m_div_points = abs(new_range.upper - old_max)/(old_max - old_min);
                graphs = m_func_collection.get_points(old_max, new_range.upper + (new_range.upper - new_range.lower)/40, m_div_points);

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
        old_min = new_range.lower;
        old_max = new_range.upper;
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
