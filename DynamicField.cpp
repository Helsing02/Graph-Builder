#include "DynamicField.h"
#include <QScrollArea>

using std::string;

DynamicField::DynamicField(QWidget* parent){
    fx =new QLabel(parent);
//    fx->setText("f(x)=");
//    string color[]={"#9AD35F", "#ecf96a", "e75480", "#89cfef", "ffd1dc", "#d7b8e9"};
//    int i=rand() % (6);
//    string str=color[i];

    fx->setText("<font color='blue'>f(x)=</font>");
    //fx->setText("QLabel{color:rgb(100,228,181);");


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

    layout=new QVBoxLayout;
    layout->addLayout(upper);
    layout->addLayout(lower);

    QAbstractButton::connect(push_button, SIGNAL(clicked()), this, SLOT(b_clicked()));
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
}

void DynamicField::b_clicked(){
    emit deleteField(this);
}

QString DynamicField::expression(){
    return input_line->text();
}

bool DynamicField::visibility(){
    return check_box->isChecked();
}
