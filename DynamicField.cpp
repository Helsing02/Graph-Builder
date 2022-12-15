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

    m_push_button = new QPushButton(this);
    m_push_button->setText("Удалить");

    m_push_button_2 = new QPushButton(this);
    m_push_button_2->setText("Цвет");

    m_layout=new QVBoxLayout(this);
    m_upper=new QHBoxLayout(this);
    m_lower=new QHBoxLayout(this);
    m_layout->addLayout(m_upper);
    m_layout->addLayout(m_lower);

    m_lower->addStretch();
    m_lower->addWidget(m_check_box);
    m_lower->addWidget(m_push_button);
    m_lower->addWidget(m_push_button_2);


    m_upper->addWidget(m_fx);
    m_upper->addWidget(m_input_line);

    QAbstractButton::connect(m_push_button, SIGNAL(clicked()), this, SLOT(b_clicked()));
    QAbstractButton::connect(m_push_button_2, SIGNAL(clicked()), this, SLOT(c_2_clicked()));

}

void DynamicField::b_clicked(){
    emit delete_field(this);
}
//для цвета
void DynamicField::c_2_clicked(){
    QColor ColorValue=QColorDialog::getColor(Qt::white);
    qDebug()<<ColorValue;
}

QString DynamicField::text(){
    return m_input_line->text();
}

bool DynamicField::visibility(){
    return m_check_box->isChecked();
}
