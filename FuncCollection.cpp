#include <iostream>
#include <vector>

using namespace std;

class FuncCollection
{
    vector <Function> arr_function;
    FuncWindow canvas; 
public:
    void AddFunc(string newfunc);
    void DeleteFunc(string oldfunc);
    void RecastGraph();
};

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

int main()
{
    // я у мамы программист
}