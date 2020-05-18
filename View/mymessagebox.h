#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit MyMessageBox(QWidget *parent = nullptr);
    ~MyMessageBox();
    qint32 init(qint32 type, QString title, QString message);
    qint32 getResult();

private slots:
    void on_pushButton_YES_clicked();
    void on_pushButton_NO_clicked();

private:
    Ui::MyMessageBox *ui;
    qint32 result = 0;
};

#endif // MYMESSAGEBOX_H
