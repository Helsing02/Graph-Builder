#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QColor>
#include "reference.h"
#include "error.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->xMin->setText("-10");
    ui->xMax->setText("10");
    ui->yMin->setEnabled(false);
    ui->yMax->setEnabled(false);

    add_dynamic_f();
    connect(ui->autoRange, SIGNAL(stateChanged(int)), this, SLOT(disable_y(int)));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_dynamic_f()));
    connect(ui->buildBtn, SIGNAL(clicked()), this, SLOT(build_graph()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::delete_dynamic_f(DynamicField* df){
    fields.remove(fields.indexOf(df));
    //ui->FuncLayout->removeWidget(df);
    delete df;
}

void MainWindow::add_dynamic_f()
{
    DynamicField* df= new DynamicField(this);
    connect(df, SIGNAL(delete_field(DynamicField*)), this, SLOT(delete_dynamic_f(DynamicField*)));
    fields.push_back(df);
    ui->FuncLayout->addWidget(df);
}

void MainWindow::build_graph(){
    FuncWindow* func_window=new FuncWindow;
    for (DynamicField* df: fields){
        if (df->visibility()){
            if (func_window->add_func(df->text().toStdString())){
                // ошибка ввода
            }
            std::cout<<(df->text()).toStdString()<<std::endl;
        }
    }

    std::cout<<std::endl;
    int x_min=((ui->xMin)->text()).toInt(), x_max=((ui->xMax)->text()).toInt(), y_min, y_max;

    func_window->add_graphs(x_min, x_max);
    func_window->change_size(x_min, x_max, x_min, x_max);

    func_window->show();
    /*
    if (ui->autoRange->isChecked()){
        y_min=xin;
        yMax=xMax;
    } else {
        yMin=((ui->yMin)->text()).toInt();
        yMax=((ui->xMax)->text()).toInt();
    }
    if (ui->ch_Pi->isChecked()){
        xMin*=3.14;
        xMax*=3.14;
    }
    */

}

void MainWindow::disable_y(int i){
    ui->yMin->setEnabled(!i);
    ui->yMax->setEnabled(!i);
    if (i){
        ui->yMin->setText("");
        ui->yMax->setText("");
    } else {
        ui->yMin->setText(ui->xMin->text());
        ui->yMax->setText(ui->xMax->text());
    }
}

void MainWindow::on_pushButton_clicked()
{
    reference window;
    window.setModal(true);
    window.exec();
}


