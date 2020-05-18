#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    box = new MyMessageBox(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();
    UserController &uc = UserController::getInstance();
    QString name = this->ui->lineEditUserName->text();
    QString password = this->ui->lineEditPassword->text();
    User* user;

    if(name == "")
    {
        box->init(0, "登录失败", "请输入用户名");
        box->exec();
    }
    else if(password == "")
    {
        box->init(0, "登录失败", "请输入密码");
        box->exec();
    }
    else
    {
        user = db.queryUser(name, User::USER_NAME);
        if(user == nullptr)
        {
            box->init(0, "登录失败", "用户不存在");
            box->exec();
        }
        else if(user->getUserPassword() != password)
        {
            box->init(0, "登录失败", "密码错误");
            box->exec();
        }
        else
        {
            box->init(1, "登录成功", "单击确认继续");
            uc.changeUser(user);
            int result = box->exec();
            if (result == QMessageBox::Accepted)
            {
                this->accept();
                this->close();
            }
        }
    }
}

void LoginDialog::on_btnRegister_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();
    QString name = this->ui->lineEditUserName->text();
    QString password = this->ui->lineEditPassword->text();
    if(name == "")
    {
        box->init(0, "注册用户失败", "请输入用户名");
        box->exec();
    }

    else if(password == "")
    {
        box->init(0, "注册用户失败", "请输入密码");
        box->exec();
    }

    else if(!db.insertUser(this->ui->lineEditUserName->text(), this->ui->lineEditPassword->text()))
    {
        box->init(0, "注册用户失败", "用户名重复");
        box->exec();
    }
    else
    {
        box->init(1, "注册成功", "单击YES继续");
        int result = box->exec();

        if (result == QMessageBox::Accepted)
            this->close();
    }
}
