#include "FuncCollection.h"

void FuncCollection::AddFunc(string newfunc)
{
    Function New(newfunc);
    arr_function.push_back(New);
}

void FuncCollection::DeleteFunc(string oldfunc)
{
    int i = 0;
    while (arr_function[i].exp != oldfunc) i++;

    arr_function.erase(arr_function.begin() + i);
}

void FuncCollection::RecastGraph()
{
    canvas.recast();
}