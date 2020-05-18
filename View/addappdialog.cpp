#include "addappdialog.h"
#include "ui_addappdialog.h"

AddAppDialog::AddAppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppDialog)
{
    ui->setupUi(this);
    box = new MyMessageBox(this);
}

AddAppDialog::~AddAppDialog()
{
    delete ui;
    delete box;
}

void AddAppDialog::on_btnAddApp_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();
    UserController &uc = UserController::getInstance();

    QString userId = uc.getInstance().getFormalUser()->getUserId();
    QString appName = this->ui->lineEditAppName->text();
    QString appVer = this->ui->lineEditAppVer->text();


    if(appName == "")
    {
        box->init(0, "新建应用失败", "请输入应用名");
        box->exec();
    }
    else if(appVer == "")
    {
        box->init(0, "新建应用失败", "请输入应用版本");
        box->exec();
    }
    else
    {
        if(!db.insertApp(userId, appName, appVer))
        {
            box->init(0, "新建应用失败", db.lastError());
            box->exec();
        }
        else
        {
            box->init(1, "新建应用成功", "点击确认继续");
            box->setModal(false);
            int result = box->exec();

            if(result == MyMessageBox::Accepted)
            {
                if (box->getResult() == 1)
                {
                    this->accept();
                    this->close();
                }
            }
        }
    }
}
