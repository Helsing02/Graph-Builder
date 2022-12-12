#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DynamicField.h"
#include "FuncWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_dynamic_f();
    void delete_dynamic_f(DynamicField* df=nullptr);
    void build_graph();
    void disable_y(int);

private:
    Ui::MainWindow *ui;
    QVector <DynamicField*> fields;

};
#endif // MAINWINDOW_H
