#include "DynamicField.h"

using std::string;

DynamicField::DynamicField(QWidget* parent){
    fx =new QLabel(parent);
    fx->setText("f(x)=");

    input_line = new QLineEdit(parent);

    check_box = new QCheckBox(parent);
    check_box->setText("Отображать");
    check_box->setChecked(true);

    push_button = new QPushButton(parent);
    push_button->setText("Удалить");

    upper=new QHBoxLayout;
    upper->addWidget(fx);
    upper->addWidget(input_line);

    lower=new QHBoxLayout;
    lower->addStretch();
    lower->addWidget(check_box);
    lower->addWidget(push_button);

    //для цвета
    push_button_2=new QPushButton(parent);
    push_button_2->setText("Цвет");
    lower->addWidget(push_button_2);


    layout=new QVBoxLayout;
    layout->addLayout(upper);
    layout->addLayout(lower);

    QAbstractButton::connect(push_button, SIGNAL(clicked()), this, SLOT(b_clicked()));
    QAbstractButton::connect(push_button_2, SIGNAL(clicked()), this, SLOT(c_2_clicked()));
}

QLayout* DynamicField::getLayout(){
    return layout;
}

DynamicField::~DynamicField(){
    delete fx;
    delete input_line;
    delete check_box;
    delete push_button;
    delete lower;
    delete upper;
    delete layout;

    delete push_button_2;
}

void DynamicField::b_clicked(){
    emit deleteField(this);
}
//для цвета
void DynamicField::c_2_clicked(){
    QColor ColorValue=QColorDialog::getColor(Qt::white);
    qDebug()<<ColorValue;
}

QString DynamicField::expression(){
    return input_line->text();
}

bool DynamicField::visibility(){
    return check_box->isChecked();
}
