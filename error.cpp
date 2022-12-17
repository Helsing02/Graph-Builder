#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(255,255,255);");
}

error::~error()
{
    delete ui;
}

void error::erro(int i){
    if(i==1)
        ui->text->setText("Ошибка связана со скобками ");
    else if(i==2)
        ui->text->setText("Некорректно введеные данные ");
    else if(i==3)
        ui->text->setText("Ошибка связана с некорректность введных операций ");
    else if(i==4)
        ui->text->setText("Строка не заполнена ");
}


