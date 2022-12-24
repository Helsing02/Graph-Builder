#include "FuncCollection.h"

int FuncCollection::add_func(std::string new_func)
{
    Function *obj = new Function;
    int flag = obj->set_exp(new_func);
    arr_func.push_back(obj);

    return flag;
}

FuncCollection:: ~FuncCollection()
{
    for (Function* f: arr_func)
    {
        delete f;
    }
}

QVector<QVector<QVector<double>>> FuncCollection::get_points(double x_min, double x_max, double m_points)
{
    QVector<QVector<QVector<double>>> graphs;

    double delta=(x_max-x_min)/(700*m_points);

    for (Function* f: arr_func)
    {
        QVector<QVector<double>> graph;
        QVector <double> x, y;
        double i=x_min;
        for(; i<=x_max; i+=delta)
        {
            x.push_back(i);
            y.push_back(f->get_y(i));
        }

        graph.push_back(x);
        graph.push_back(y);

        graphs.push_back(graph);
    }

    return graphs;
}

