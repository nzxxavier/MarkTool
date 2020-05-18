#ifndef ADDAPPDIALOG_H
#define ADDAPPDIALOG_H

#include <QDialog>
#include "Controller/databasecontroller.h"
#include "Controller/usercontroller.h"
#include "mymessagebox.h"

namespace Ui {
class AddAppDialog;
}

class AddAppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppDialog(QWidget *parent = nullptr);
    ~AddAppDialog();

private slots:
    void on_btnAddApp_clicked();

private:
    Ui::AddAppDialog *ui;
    MyMessageBox* box;
};

#endif // ADDAPPDIALOG_H
