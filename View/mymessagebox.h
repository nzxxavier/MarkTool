#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MyMessageBox(QWidget *parent = nullptr);
    ~MyMessageBox();

private:
    Ui::MyMessageBox *ui;
};

#endif // MYMESSAGEBOX_H
