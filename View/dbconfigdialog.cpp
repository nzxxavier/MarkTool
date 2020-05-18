#include "dbconfigdialog.h"
#include "ui_dbconfigdialog.h"

DBConfigDialog::DBConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConfigDialog)
{
    ui->setupUi(this);
    box = new MyMessageBox(this);
}

DBConfigDialog::~DBConfigDialog()
{
    delete ui;
}

void DBConfigDialog::on_btnConnect_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();

    QString url = ui->lineEditUrl->text() == "" ? "127.0.0.1" : ui->lineEditUrl->text();
    QString name = ui->lineEditUserName->text() == "" ? "root" : ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text() == "" ? "nzx123" : ui->lineEditPassword->text();
    QString database = ui->lineEditDB->text() == "" ? "marktool" : ui->lineEditDB->text();

    if(!db.initConnection(url, name, password, database))
    {
        box->init(0, "数据库连接错误", db.lastError());
        box->exec();
    }
    else
        this->close();
}
