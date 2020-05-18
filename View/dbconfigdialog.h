#ifndef DBCONFIGDIALOG_H
#define DBCONFIGDIALOG_H

#include <QDialog>
#include <Controller/databasecontroller.h>
#include "mymessagebox.h"

namespace Ui {
class DBConfigDialog;
}

class DBConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DBConfigDialog(QWidget *parent = nullptr);
    ~DBConfigDialog();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::DBConfigDialog *ui;
    MyMessageBox* box;
};

#endif // DBCONFIGDIALOG_H
