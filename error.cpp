#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    setWindowTitle("ERROR");
    this->setStyleSheet("background-color:rgb(255,255,255);");
}

error::~error()
{
    delete ui;
}

void error::erro(int i){
    if(i==1)
        ui->text->setText("Некорректно введена формула ");
    else if(i==5)
        ui->text->setText("Посторонний символ при задании интервала");
    else if(i==6)
        ui->text->setText("Интервал задан неверно");
    else if(i==7)
        ui->text->setText("Размер интервала неверный");
}


