#include "FuncCollection.h"

int FuncCollection::add_func(std::string )
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

QVector<QVector<QVector<double>>> FuncCollection::get_points(int x_min, int x_max)
{
    QVector<QVector<QVector<double>>> graphs;
    QVector<QVector<double>> graph;

    double delta=((double)x_max-(double)x_min)/10000;

    for (Function* f: arr_func)
    {
        QVector <double> x, y;
        double i=x_min;
        for(; i<=x_max; i+=delta)
        {
            x.push_back(i);
            y.push_back(f->GetY(i));
        }

        graph.push_back(x);
        graph.push_back(y);

        graphs.push_back(graph);
    }

    return graphs;
}

