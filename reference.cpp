#include "reference.h"
#include "ui_reference.h"
#include <QColor>

reference::reference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reference)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(255,228,181);");
    //КАРТИНКИ ПУТЬ ARGV[0]
    //label_2

}

reference::~reference()
{
    delete ui;
}
