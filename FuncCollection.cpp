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
    double m_inf = pow(2,12);
    double delta=(x_max-x_min)/(10000*m_points);

    for (Function* f: arr_func)
    {
        QVector<QVector<double>> graph;
        QVector <double> x, y;
        double i=x_min;
        double tmp_x, tmp_y;
        for(; i<=x_max; i+=delta)
        {
            x.push_back(i);
            y.push_back(f->get_y(i));

/*            if(y.count() >= 4 && (fabs(y[y.count() - 4] - y[y.count() - 3]) +
                    fabs(y[y.count() - 2] - y[y.count() - 1]) < fabs(y[y.count() - 3] - y[y.count() - 2])))
            {
                if(y[y.count() - 3] > y[y.count() - 2])
                {
                    y[y.count() - 3] = m_inf;
                    tmp_y = y[y.count() - 1];
                    y.pop_back();
                    y.pop_back();

                    tmp_x = x[x.count() - 1];
                    x.pop_back();
                    x.pop_back();

                    graph.push_back(x);
                    graph.push_back(y);

                    graphs.push_back(graph);

                    graph.clear();

                    x.clear();
                    y.clear();

                    x.push_back(tmp_x - delta);
                    y.push_back(-m_inf);

                    x.push_back(tmp_x);
                    y.push_back(tmp_y);
                }
                else
                {
                    y[y.count() - 3] = -m_inf;
                    tmp_y = y[y.count() - 1];
                    y.pop_back();
                    y.pop_back();

                    tmp_x = x[x.count() - 1];
                    x.pop_back();
                    x.pop_back();

                    graph.push_back(x);
                    graph.push_back(y);

                    graphs.push_back(graph);

                    graph.clear();

                    x.clear();
                    y.clear();

                    x.push_back(tmp_x - delta);
                    y.push_back(m_inf);

                    x.push_back(tmp_x);
                    y.push_back(tmp_y);
                }
            }
*/
            /*
            if(y.count() >= 4 && (fabs(y[y.count() - 4] - y[y.count() - 3]) +
                    fabs(y[y.count() - 2] - y[y.count() - 1]) < fabs(y[y.count() - 3] - y[y.count() - 2])))
            {
                if(y[y.count() - 3] > y[y.count() - 2])
                {
                    tmp_y = y[y.count() - 1];
                    tmp_x = x[x.count() - 1];

                    y[y.count() - 3] = m_inf;
                    y[y.count() - 2] = std::numeric_limits<double>::quiet_NaN();
                    y[y.count() - 1] = -m_inf;

                    x[x.count() - 1] = x[x.count() - 2];
                    x[x.count() - 2] = x[x.count() - 2] - (delta / 2);

                    x.push_back(tmp_x);
                    y.push_back(tmp_y);
                }
                else
                {
                    y[y.count() - 3] = -m_inf;
                    y[y.count() - 2] = std::numeric_limits<double>::quiet_NaN();
                    y[y.count() - 1] = m_inf;

                    x[x.count() - 1] = x[x.count() - 2];
                    x[x.count() - 2] = x[x.count() - 2] - (delta / 2);

                    i -= delta;
                }
            }
            */


        }

        graph.push_back(x);
        graph.push_back(y);

        graphs.push_back(graph);
    }

    return graphs;
}

