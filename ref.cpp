#include "ref.h"
#include "ui_ref.h"

Ref::Ref(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ref)
{
    ui->setupUi(this);
}

Ref::~Ref()
{
    delete ui;
}
