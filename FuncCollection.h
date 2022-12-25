#include <vector>
#include <QVector>
#include <cmath>

#include "Function.h"



class FuncCollection
{
    std::vector <Function*> arr_func;

public:
    ~FuncCollection();
    int add_func(std::string);
    QVector<QVector<QVector<double>>> get_points(double, double, double m_points = 1);
};
