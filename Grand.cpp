#include "Grand.h"
#include "mainwindow.h"
#include "FuncWindow.h"
#include "error.h"


Grand::Grand()
{
    w_main=new MainWindow;

    connect(w_main, SIGNAL(build_signal()), this, SLOT(build_graph()));
    connect(w_main, SIGNAL(close()), this, SLOT(close_app()));
    w_main->show();
}

Grand::~Grand()
{
    std::cout<<"grand deleted\n";
    w_func.back()->close();
    w_func.pop_back();
}

void Grand::build_graph()
{
    FuncWindow* func_window=new FuncWindow;
    QVector <QString> expressions=w_main->get_exp();
    QVector <QColor> colors=w_main->get_cols();
    for(int j=0; j<expressions.size(); j++){
        w_func.push_back(func_window);
        if(int i=func_window->add_func(expressions[j], colors[j])!=0){
            // ошибка ввода
            delete func_window;
            error* window_err=new error;
            window_err->erro(i);
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
    w_func.push_back(func_window);
    func_window->show();
}

void Grand::close_app()
{
    delete this;
}


