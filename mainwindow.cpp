#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QColor>
#include <iostream>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->xMin->setText("-10");
    ui->xMax->setText("10");
    ui->yMin->setEnabled(false);
    ui->yMax->setEnabled(false);

    add_dynamic_f();
    connect(ui->autoRange, SIGNAL(stateChanged(int)), this, SLOT(set_enabled_auto_range(int)));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_dynamic_f()));
    connect(ui->buildBtn, SIGNAL(clicked()), this, SLOT(build_graph()));
    connect(ui->refBtn, SIGNAL(clicked()), this, SLOT(show_ref()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector <QString> MainWindow::get_exp()
{
    QVector<QString> to_ret;
    for (DynamicField* df : fields){
        if(df->disp_is_checked()){
            to_ret.push_back(df->get_exp());
        }
    }
    return to_ret;
}

QVector <QColor> MainWindow::get_cols()
{
    QVector<QColor> to_ret;
    for (DynamicField* df : fields){
        if(df->disp_is_checked()){
            to_ret.push_back(df->get_color());
        }
    }
    return to_ret;
}

QVector <double> MainWindow::get_range()
{
    QVector <double> to_ret;
    to_ret.push_back(((ui->xMin)->text()).toDouble());
    to_ret.push_back(((ui->xMax)->text()).toDouble());
    if (ui->autoRange->isChecked()){
        to_ret.push_back(((ui->xMin)->text()).toDouble());
        to_ret.push_back(((ui->xMax)->text()).toDouble());
    } else {
        to_ret.push_back(((ui->yMin)->text()).toDouble());
        to_ret.push_back(((ui->yMax)->text()).toDouble());
    }
    return to_ret;
}

bool MainWindow::auto_range_is_checked()
{
    return ui->autoRange->isChecked();
}

bool MainWindow::is_range_in_pi()
{
    return ui->ch_Pi->isChecked();
}

void MainWindow::add_dynamic_f()
{
    DynamicField* df= new DynamicField(this);
    connect(df, SIGNAL(delete_field(DynamicField*)), this, SLOT(delete_dynamic_f(DynamicField*)));
    fields.push_back(df);
    ui->FuncLayout->addWidget(df);
}

void MainWindow::delete_dynamic_f(DynamicField* df)
{
    fields.remove(fields.indexOf(df));
    delete df;
}

void MainWindow::set_enabled_auto_range(int f)
{
    ui->yMin->setEnabled(!f);
    ui->yMax->setEnabled(!f);
    if (!f){
        ui->yMin->setText(ui->xMin->text());
        ui->yMax->setText(ui->xMax->text());
    } else {
        ui->yMin->setText("");
        ui->yMax->setText("");
    }
}

void MainWindow::show_ref()
{
    Ref* window=new Ref(this);
    window->show();
}

void MainWindow::build_graph()
{
    emit build_signal();
}


void MainWindow::close_event(QCloseEvent* event){
    emit close_w();
    event->accept();
}
