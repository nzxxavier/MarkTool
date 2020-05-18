#include "mymessagebox.h"
#include "ui_mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

qint32 MyMessageBox::init(qint32 type, QString title, QString message)
{
    this->setWindowTitle(title);
    ui->label->setText(message);
    this->setModal(false);
    QString fileName;
    if (type == 0)
        fileName = ":/img/wrong.png";
    else
        fileName = ":/img/right.png";
    QPixmap img(fileName);
    img = img.scaled(100, 100);
    ui->label_img->setPixmap(img);
    ui->label_img->show();
    this->show();
}

void MyMessageBox::on_pushButton_YES_clicked()
{
    this->result = 1;
    this->accept();
    this->close();
}

void MyMessageBox::on_pushButton_NO_clicked()
{
    this->result = 0;
    this->accept();
    this->close();
}

qint32 MyMessageBox::getResult()
{
    return this->result;
}
