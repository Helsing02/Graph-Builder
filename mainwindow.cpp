#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QColor>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_addBtn_clicked();
    //this->setStyleSheet("background-color:rgb(255,246,230);");
}

MainWindow::~MainWindow()
{
    for (DynamicField* df: fields){
        delete df;
    }
    delete ui;
}


void MainWindow::delete_Dfield(DynamicField* df){
    fields.remove(fields.indexOf(df));
    ui->FuncLayoutMain->removeItem(df->getLayout());
    delete df;
}

void MainWindow::on_addBtn_clicked()
{
    DynamicField* field_to_add= new DynamicField(this);
    connect(field_to_add, SIGNAL(deleteField(DynamicField*)), this, SLOT(delete_Dfield(DynamicField*)));
    fields.push_back(field_to_add);
    ui->FuncLayoutMain->addLayout(field_to_add->getLayout());

}


