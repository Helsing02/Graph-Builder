#include "reference.h"
#include "ui_reference.h"
#include <QColor>

reference::reference(QWindow *parent) :
    QWindow(parent),
    ui(new Ui::reference)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(255,228,181);");
    //setModal(false);
}

reference::~reference()
{
    delete ui;
}
