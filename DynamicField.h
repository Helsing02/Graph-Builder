#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <string>

class DynamicField: public QWidget
{
    Q_OBJECT
private:
    QLabel* m_fx;
    QLineEdit* m_input_line;
    QCheckBox* m_check_box;
    QPushButton* m_push_button;
    QVBoxLayout* m_layout;
    QHBoxLayout* m_upper;
    QHBoxLayout* m_lower;

public:
    DynamicField(QWidget* parent=nullptr);
    QString text();
    bool visibility();

private slots:
    void b_clicked();
    void c_2_clicked();
signals:
    void delete_field(DynamicField*);



};
