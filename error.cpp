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
