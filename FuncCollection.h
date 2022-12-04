#include <vector>
#include "Function.h"
#include "FuncWindow.h"


class FuncCollection
{
    std::vector <Function*> arr_function;
    FuncWindow* canvas;
public:
    FuncCollection();
    ~FuncCollection();
    void AddFunc(std::string);
    void DeleteFunc(int);
    void RecastGraph(int, int, int, int);

    void tempClear();
};
