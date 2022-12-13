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
    //this->setStyleSheet("background-color:rgb(255,228,181);");

    ui->xMin->setText("-10");
    ui->xMax->setText("10");
    ui->yMin->setEnabled(false);
    ui->yMax->setEnabled(false);


    collection = new FuncCollection;
    add_Dfield();
    connect(ui->autoRange, SIGNAL(stateChanged(int)), this, SLOT(disableY(int)));
    QAbstractButton::connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_Dfield()));
    QAbstractButton::connect(ui->buildBtn, SIGNAL(clicked()), this, SLOT(build_graph()));

}

MainWindow::~MainWindow()
{
    for (DynamicField* df: fields){
        delete df;
    }
    delete collection;
    delete ui;
}


void MainWindow::delete_Dfield(DynamicField* df){
    collection->DeleteFunc(fields.indexOf(df));
    fields.remove(fields.indexOf(df));
    ui->FuncLayoutMain->removeItem(df->getLayout());
    delete df;
}

void MainWindow::add_Dfield()
{
    DynamicField* field_to_add= new DynamicField(this);
    connect(field_to_add, SIGNAL(deleteField(DynamicField*)), this, SLOT(delete_Dfield(DynamicField*)));
    fields.push_back(field_to_add);
    collection->AddFunc("1");
    ui->FuncLayoutMain->addLayout(field_to_add->getLayout());

}

void MainWindow::build_graph(){
    collection->tempClear();
    for (DynamicField* df: fields){
        if (df->visibility()){
            collection->AddFunc((df->expression()).toStdString());
            std::cout<<(df->expression()).toStdString()<<std::endl;
        }
    }
    std::cout<<std::endl;
    int xMin=((ui->xMin)->text()).toInt(), xMax=((ui->xMax)->text()).toInt(), yMin, yMax;
    if (ui->autoRange->isChecked()){
        yMin=xMin;
        yMax=xMax;
    } else {
        yMin=((ui->yMin)->text()).toInt();
        yMax=((ui->xMax)->text()).toInt();
    }
    if (ui->ch_Pi->isChecked()){
        xMin*=3.14;
        xMax*=3.14;
    }
    collection->RecastGraph(xMin, xMax, yMin, yMax);


}

void MainWindow::disableY(int i){
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


