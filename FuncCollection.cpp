#include "FuncCollection.h"

FuncCollection::FuncCollection(){
    canvas=new FuncWindow();
}

void FuncCollection::AddFunc(std::string newfunc)
{
    arr_function.push_back(new Function(newfunc));
}

FuncCollection:: ~FuncCollection(){
    for (Function* f: arr_function){
        delete f;
    }
    delete canvas;
}

void FuncCollection::DeleteFunc(int i)
{
    arr_function.erase(arr_function.begin() + i);
}


void FuncCollection::RecastGraph(int xMin, int xMax, int yMin, int yMax)
{
    canvas->changeSize(xMin, xMax, yMin, yMax);
    int index=0;
    double delta=((float)xMax-(float)xMin)/100000;
    canvas->clearGraphs();
    for (Function* f: arr_function){
        QVector <double> x, y;
        double i=xMin;
        for(; i<=xMax; i+=delta){
            x.push_back(i);
            y.push_back(f->GetY(i));
        }
        canvas->addGraph(x, y, index);
        index++;
    }
    canvas->replot();
    canvas->show();
}

void FuncCollection::tempClear(){
    for(Function* f: arr_function){
        delete f;
    }
    arr_function.clear();
}

