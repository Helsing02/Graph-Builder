#include "DynamicField.h"
#include <QColorDialog>

DynamicField::DynamicField(QWidget* parent):
    QWidget(parent)
{

    m_fx =new QLabel(this);
    m_fx->setText("f(x)=");

    m_input_line = new QLineEdit(this);

    m_check_box = new QCheckBox(this);
    m_check_box->setText("Отображать");
    m_check_box->setChecked(true);

    m_btn_delete = new QPushButton(this);
    m_btn_delete->setText("Удалить");

    m_btn_color = new QPushButton(this);
    m_btn_color->setText("Цвет");

    m_layout=new QVBoxLayout(this);
    m_upper=new QHBoxLayout(this);
    m_lower=new QHBoxLayout(this);
    m_layout->addLayout(m_upper);
    m_layout->addLayout(m_lower);

    m_lower->addStretch();
    m_lower->addWidget(m_check_box);
    m_lower->addWidget(m_btn_delete);
    m_lower->addWidget(m_btn_color);

    m_upper->addWidget(m_fx);
    m_upper->addWidget(m_input_line);

    m_color=new QColor;
    m_color->setRgb(102, 0, 204);

    QAbstractButton::connect(m_btn_delete, SIGNAL(clicked()), this, SLOT(del_btn_clicked()));
    QAbstractButton::connect(m_btn_color, SIGNAL(clicked()), this, SLOT(col_btn_clicked()));

}

QString DynamicField::get_exp(){
    return m_input_line->text();
}

QRgb DynamicField::get_color(){
    return m_color->rgb();
}

bool DynamicField::disp_is_checked(){
    return m_check_box->isChecked();
}
//для цвета
void DynamicField::c_2_clicked(){
    QColor ColorValue=QColorDialog::getColor(Qt::white);
    qDebug()<<ColorValue;
}

void DynamicField::del_btn_clicked(){
    emit delete_field(this);
}

//для цвета
void DynamicField::col_btn_clicked(){
    QColor ColorValue=QColorDialog::getColor(Qt::white);
    qDebug()<<ColorValue;
}
