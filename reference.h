#ifndef REFERENCE_H
#define REFERENCE_H

#include <QWindow>

namespace Ui {
class reference;
}

class reference : public QWindow
{
    Q_OBJECT

public:
    explicit reference(QWindow *parent = nullptr);
    ~reference();

private:
    Ui::reference *ui;
};

#endif // REFERENCE_H
