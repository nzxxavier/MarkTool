#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "Controller/databasecontroller.h"
#include "Controller/usercontroller.h"
#include "mymessagebox.h"


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

    void on_btnRegister_clicked();

private:
    Ui::LoginDialog *ui;
    MyMessageBox* box;
};

#endif // LOGINDIALOG_H
