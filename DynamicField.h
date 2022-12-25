#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>

class DynamicField: public QWidget
{
    Q_OBJECT
private:
    QLabel* m_fx;
    QLineEdit* m_input_line;
    QCheckBox* m_check_box;
    QPushButton* m_btn_delete;
    QPushButton* m_btn_color;
    QVBoxLayout* m_layout;
    QHBoxLayout* m_upper;
    QHBoxLayout* m_lower;
    QColor m_color;

public:
    DynamicField(QWidget* parent=nullptr);
    QString get_exp();
    QColor get_color();
    bool disp_is_checked();

private slots:
    void del_btn_clicked();
    void col_btn_clicked();
signals:
    void delete_field(DynamicField*);
};
