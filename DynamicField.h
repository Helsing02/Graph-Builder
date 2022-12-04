#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>

#pragma once

class DynamicField: public QObject{
    Q_OBJECT
private:
    QLabel* fx;
    QLineEdit* input_line;
    QCheckBox* check_box;
    QPushButton* push_button;
    QVBoxLayout* layout;
    QHBoxLayout* upper;
    QHBoxLayout* lower;

public:
    DynamicField(QWidget* parent=0);
    QLayout* getLayout();
    ~DynamicField();

private slots:
    void b_clicked();
signals:
    void deleteField(DynamicField*);



};
