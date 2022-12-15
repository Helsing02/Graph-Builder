#include "Grand.h"
#include "mainwindow.h"
#include "FuncWindow.h"
#include "error.h"
#include "DynamicField.h"

Grand::Grand(){
    MainWindow* w_main;
}

Grand::~Grand(){
    w_func.back()->close();
    w_func.pop_back();
}

void Grand::build_graph(){
    FuncWindow* func_window=new FuncWindow;
    bool flag=true;
    for(int j=0; j<w_main->fields.size(); j++){
        w_func.push_back(func_window);
        if(int i=add_func(w_main->get_exp(), w_main->get_colls)!=0){
            // ошибка ввода
            error* window_err=new error;
            window_err->erro(i);
            window_err->setModal(true);
            window_err->show();
            flag=false;
        }
    }
    if(flag){//в каких пределах находится
        Qvector ran=w_main->get_range();
        if(w_main->is_range_in_pi())
            func_window->set_range_pi(ran[0], ran[1]);
        else if(w_main->auto_range_is_checked()){
            change_range_x(ran[0], ran[1]);
            func_window->find_range_y();
        }
        else{
            func_window->change_range_x(ran[0], ran[1]);
            func_window->change_range_y(ran[2], ran[3]);
        }
        func_window->show();
    }

    flag=true;

}

//void Grand::build_graph(){
//    FuncWindow* func_window=new FuncWindow;
//    bool flag=true;
//    for (DynamicField* df: fields){
//        if (df->visibility()){
//            int i=func_window->add_func(df->text().toStdString());
//            std::cout<<i;
//            if (i!=0){
//                // ошибка ввода
//                error* window_err=new error;
//                window_err->erro(i);
//                window_err->setModal(true);
//                window_err->show();
//                flag=false;
//            }
//        }
//    }
//    if(flag){
//        int x_min=((ui->xMin)->text()).toInt(), x_max=((ui->xMax)->text()).toInt(), y_min, y_max;

//        func_window->add_graphs(x_min, x_max);
//        func_window->change_size(x_min, x_max, x_min, x_max);

//        func_window->show();
//    }
//    flag=true;
//    /*
//    if (ui->autoRange->isChecked()){
//        y_min=xin;
//        yMax=xMax;
//    } else {
//        yMin=((ui->yMin)->text()).toInt();
//        yMax=((ui->xMax)->text()).toInt();
//    }
//    if (ui->ch_Pi->isChecked()){
//        xMin*=3.14;
//        xMax*=3.14;
//    }
//    */

//}
