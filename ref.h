#ifndef REF_H
#define REF_H

#include <QMainWindow>

namespace Ui {
class Ref;
}

class Ref : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ref(QWidget *parent = nullptr);
    ~Ref();

private:
    Ui::Ref *ui;
};

#endif // REF_H
