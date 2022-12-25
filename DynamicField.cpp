#include "DynamicField.h"

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

    m_color=0x880033ff;

    QAbstractButton::connect(m_btn_delete, SIGNAL(clicked()), this, SLOT(del_btn_clicked()));
    QAbstractButton::connect(m_btn_color, SIGNAL(clicked()), this, SLOT(col_btn_clicked()));

}

QString DynamicField::get_exp()
{
    return m_input_line->text();
}

QColor DynamicField::get_color()
{
    return m_color;
}

bool DynamicField::disp_is_checked()
{
    return m_check_box->isChecked();
}
//для цвета
void DynamicField::col_btn_clicked()
{
    m_color=QColorDialog::getColor(Qt::white);
    m_btn_color->setStyleSheet( QString("background-color: %1").arg(m_color.name()));
}

void DynamicField::del_btn_clicked()
{
    emit delete_field(this);
}
