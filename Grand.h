#include "mainwindow.h"
#include "FuncWindow.h"

class Grand{
private:
    MainWindow* w_main;
    QVector <FuncWindow*> w_func;
public:
    Grand();
    ~Grand();
    void build_graph();
};
