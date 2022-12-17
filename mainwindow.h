#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DynamicField.h"
#include "ref.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <QString> get_exp();
    QVector <QRgb> get_cols();
    QVector <double> get_range();
    bool auto_range_is_checked();
    bool is_range_in_pi ();

private slots:
    void add_dynamic_f();
    void delete_dynamic_f(DynamicField* df=nullptr);
    void set_enabled_auto_range(bool);
    void show_ref();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector <DynamicField*> fields;
    Ref* ref;

};
#endif // MAINWINDOW_H
