#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DynamicField.h"
#include "qscrollarea.h"
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
    QVector <QColor> get_cols();
    QVector <double> get_range(bool&);
    bool auto_range_is_checked();
    bool is_range_in_pi ();

private:
    void close_event(QCloseEvent* event);

private slots:
    void add_dynamic_f();
    void delete_dynamic_f(DynamicField* df=nullptr);
    void set_enabled_auto_range(int);
    void show_ref();
    void build_graph();

signals:
    void build_signal();
    void close_w();

private:
    Ui::MainWindow *ui;
    QVector <DynamicField*> fields;
    Ref* ref;
    QScrollArea* scrollArea;
    QVBoxLayout *labelLayout;
    QWidget* scrollArea_content;

};
#endif // MAINWINDOW_H
