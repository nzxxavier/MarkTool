#include "myscrollwidget.h"
#include "ui_myscrollwidget.h"

MyScrollWidget::MyScrollWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyScrollWidget)
{
    ui->setupUi(this);
}

void MyScrollWidget::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

MyScrollWidget::~MyScrollWidget()
{
    delete ui;
}

void MyScrollWidget::initValue(QString appName, QString appVer, qint32 commentNum, QString lastTime)
{
    ui->labelAppName->setText(appName);
    ui->labelAppVer->setText(appVer);
    ui->labelCMTNum->setText(QString("%1").arg(commentNum));
    ui->labelLastTime->setText(lastTime);
}

void MyScrollWidget::on_btn_edit_clicked()
{
    emit myscrollwidget_edit_clicked(ui->labelAppName->text());
}

void MyScrollWidget::on_btn_delete_clicked()
{
    emit myscrollwidget_delete_clicked(ui->labelAppName->text());
}


void MyScrollWidget::on_btn_correct_clicked()
{
    emit myscrollwidget_correct_clicked(ui->labelAppName->text());
}

void MyScrollWidget::on_btn_data_clicked()
{
    emit myscrollwidget_data_clicked(ui->labelAppName->text());
}
