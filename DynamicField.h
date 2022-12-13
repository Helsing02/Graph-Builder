#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <string>

#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>

#pragma once

class DynamicField: public QObject
{
    Q_OBJECT
private:
    QLabel* fx;
    QLineEdit* input_line;
    QCheckBox* check_box;
    QPushButton* push_button;
    QPushButton* push_button_2;
    QVBoxLayout* layout;
    QHBoxLayout* upper;
    QHBoxLayout* lower;

public:
    DynamicField(QWidget* parent=0);
    ~DynamicField();
    QLayout* getLayout();
    QString expression();
    bool visibility();

private slots:
    void b_clicked();
    void c_2_clicked();
signals:
    void deleteField(DynamicField*);
    void colorGraphic(DynamicField*);
};
