#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DynamicField.h"
#include "FuncCollection.h"

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
    void add_Dfield();
    void delete_Dfield(DynamicField* df=0);
    void build_graph();
    void disableY(int);

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    QVector <DynamicField*> fields;
    FuncCollection * collection;

};
#endif // MAINWINDOW_H
