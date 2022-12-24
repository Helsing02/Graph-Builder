#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    setWindowTitle("ERROR");
    this->setStyleSheet("background-color:rgb(255,255,255);");
    ui->text->setText("Данные введены некорректно ");//
}

error::~error()
{
    delete ui;
}

void error::erro(){
    ui->text->setText("Интервал введен некорректно ");//
}

