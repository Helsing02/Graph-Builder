#include "reference.h"
#include "ui_reference.h"
#include <QColor>

reference::reference(QWindow *parent) :
    QWindow(parent),
    ui(new Ui::reference)
{
    ui->setupUi(this);
}

reference::~reference()
{
    delete ui;
}
