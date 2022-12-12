#include <vector>
#include "Function.h"
<<<<<<< HEAD


class FuncCollection
{
    std::vector <Function*> arr_function;
    //FuncWindow* canvas;
=======
#include <QVector>

class FuncCollection
{
    std::vector <Function*> arr_func;
>>>>>>> Vlad
public:
    ~FuncCollection();
    int add_func(std::string);
    QVector<QVector<QVector<double>>> get_points(int, int);
};
