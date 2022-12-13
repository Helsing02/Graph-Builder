#include "DynamicField.h"
#include <QScrollArea>

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

    m_layout=new QVBoxLayout(this);
    m_upper=new QHBoxLayout(this);
    m_lower=new QHBoxLayout(this);
    m_layout->addLayout(m_upper);
    m_layout->addLayout(m_lower);

    m_lower->addStretch();
    m_lower->addWidget(m_check_box);
    m_lower->addWidget(m_push_button);


    m_upper->addWidget(m_fx);
    m_upper->addWidget(m_input_line);

    QAbstractButton::connect(m_push_button, SIGNAL(clicked()), this, SLOT(b_clicked()));

}

void DynamicField::b_clicked(){
    emit delete_field(this);
}

QString DynamicField::text(){
    return m_input_line->text();
}

bool DynamicField::visibility(){
    return m_check_box->isChecked();
}
