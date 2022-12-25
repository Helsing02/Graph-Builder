#include "mainwindow.h"
#include "FuncWindow.h"

class Grand: public QObject{
    Q_OBJECT
private:
    MainWindow* w_main;
public:
    Grand();
private slots:
    void build_graph();
    void close_app();


};
