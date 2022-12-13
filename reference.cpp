#include "reference.h"
#include "ui_reference.h"
#include <QColor>

reference::reference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reference)
{
    ui->setupUi(this);
}

reference::~reference()
{
    delete ui;
}
