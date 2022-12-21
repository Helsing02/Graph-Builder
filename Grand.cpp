#include "Grand.h"
#include "mainwindow.h"
#include "FuncWindow.h"
#include "error.h"


Grand::Grand()
{
    w_main=new MainWindow;

    connect(w_main, SIGNAL(build_signal()), this, SLOT(build_graph()));
    connect(w_main, SIGNAL(close_w()), this, SLOT(close_app()));
    w_main->show();
}

void Grand::build_graph()
{
    FuncWindow* func_window=new FuncWindow(w_main);
    QVector <QString> expressions=w_main->get_exp();
    QVector <QColor> colors=w_main->get_cols();
    for(int j=0; j<expressions.size(); j++){
        int i=func_window->add_func(expressions[j], colors[j]);
        if(i!=0){
            // ошибка ввода
            delete func_window;
            error* window_err=new error;
//            window_err->erro(i);
            window_err->setModal(true);
            window_err->show();
            return;
        }
    }
    func_window->add_graphs(0, 5);
    QVector <double> ran=w_main->get_range();
    if(w_main->is_range_in_pi()){
        func_window->set_range_pi(ran[0], ran[1]);
    }
    else {
        func_window->change_range_x(ran[0], ran[1]);
    }

    if(w_main->auto_range_is_checked()){
        func_window->find_range_y();
    }
    else{
        func_window->change_range_y(ran[2], ran[3]);
    }
    func_window->show();
}

void Grand::close_app()
{
    delete this;
}


