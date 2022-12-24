#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QColor>
#include <iostream>
#include <QCloseEvent>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->xMin->setText("-10");
    ui->xMax->setText("10");
    ui->yMin->setEnabled(false);
    ui->yMax->setEnabled(false);

    scrollArea=new QScrollArea(this);
    ui->FuncLayout->addWidget(scrollArea);
    scrollArea_content=new QWidget();
    labelLayout=new QVBoxLayout(scrollArea_content);
    scrollArea->setWidget(scrollArea_content);
    scrollArea->setWidgetResizable(true);
    labelLayout->addStretch();
//    labelLayout= new QVBoxLayout(scrollArea);
//    scrollLayot= new QVBoxLayout;
//    QVBoxLayout *layout = new QVBoxLayout;

    add_dynamic_f();
    connect(ui->autoRange, SIGNAL(stateChanged(int)), this, SLOT(set_enabled_auto_range(int)));
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_dynamic_f()));
    connect(ui->buildBtn, SIGNAL(clicked()), this, SLOT(build_graph()));
    connect(ui->refBtn, SIGNAL(clicked()), this, SLOT(show_ref()));

    setWindowTitle("GraphicsLab");
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

QVector <double> MainWindow::get_range(bool &flag)
{
    QVector <double> to_ret;
    double x1=(ui->xMax)->text().toDouble(&flag);
    if (flag){
        double x2=(ui->xMin)->text().toDouble(&flag);
        if(flag){
            if(x1<=x2)
                flag=false;
            else{
                to_ret.push_back(x1);
                to_ret.push_back(x2);
                if (ui->autoRange->isChecked()){
                    to_ret.push_back(((ui->xMin)->text()).toDouble());
                    to_ret.push_back(((ui->xMax)->text()).toDouble());
                } else {
                    double y1=(ui->yMax)->text().toDouble(&flag);
                    if (flag){
                        to_ret.push_back(y1);
                        double y2=(ui->yMin)->text().toDouble(&flag);
                        to_ret.push_back(y2);
                        if(flag&&y1<=y2)
                            flag=false;
                    }
                }
            }
        }
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
//    QVBoxLayout* labelLayout=new QVBoxLayout(scrollArea);

    DynamicField* df= new DynamicField(scrollArea_content);
//    scrollArea = new QScrollArea;
//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setWidget(df);
    int count=labelLayout->count();
    labelLayout->insertWidget(count-1, df);

    connect(df, SIGNAL(delete_field(DynamicField*)), this, SLOT(delete_dynamic_f(DynamicField*)));
    fields.push_back(df);


//    ui->FuncLayout->addWidget(df);
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
