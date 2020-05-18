#include "mymessagebox.h"
#include "ui_mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}
