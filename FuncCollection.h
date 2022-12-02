#include <iostream>
#include <vector>
#include "Function.h"
//#include "FuncWindow.h"

using namespace std;

class FuncCollection
{
    vector <Function> arr_function;
    //FuncWindow canvas;
public:
    void AddFunc(string newfunc);
    void DeleteFunc(string oldfunc);
    void RecastGraph();
};
