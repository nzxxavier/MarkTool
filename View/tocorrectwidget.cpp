#include "tocorrectwidget.h"
#include "ui_tocorrectwidget.h"

ToCorrectWidget::ToCorrectWidget(QString userName, qint32 markClass, qint32 markCreddit, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ToCorrectWidget)
{
    ui->setupUi(this);
    ui->label_userName->setText(userName);
    setMarkClassLabel(markClass);
    setMarkCreddit(markCreddit);
}

ToCorrectWidget::~ToCorrectWidget()
{
    delete ui;
}

void ToCorrectWidget::setMarkClassLabel(qint32 markClass)
{
    switch (markClass) {
        case 1:
            ui->label_markClass->setText("功能性需求");
            break;
        case 2:
            ui->label_markClass->setText("非功能性需求");
            break;
        case 3:
            ui->label_markClass->setText("性能");
            break;
        case 4:
            ui->label_markClass->setText("兼容性");
            break;
        case 5:
            ui->label_markClass->setText("可用性");
            break;
        case 6:
            ui->label_markClass->setText("可靠性");
            break;
        case 7:
            ui->label_markClass->setText("安全性");
            break;
        case 8:
            ui->label_markClass->setText("可维护性");
            break;
        case 9:
            ui->label_markClass->setText("可移植性");
            break;
        case 10:
            ui->label_markClass->setText("其它");
            break;
        default:
            ui->label_markClass->setText("错误信息");
            break;
    }
}

void ToCorrectWidget::setMarkCreddit(qint32 markCreddit)
{
    switch (markCreddit) {
        case 1:
            ui->btn_Star1->setFlat(true);
            ui->btn_Star2->setFlat(false);
            ui->btn_Star3->setFlat(false);
            ui->btn_Star4->setFlat(false);
            ui->btn_Star5->setFlat(false);
            break;
        case 2:
            ui->btn_Star1->setFlat(true);
            ui->btn_Star2->setFlat(true);
            ui->btn_Star3->setFlat(false);
            ui->btn_Star4->setFlat(false);
            ui->btn_Star5->setFlat(false);
            break;
        case 3:
            ui->btn_Star1->setFlat(true);
            ui->btn_Star2->setFlat(true);
            ui->btn_Star3->setFlat(true);
            ui->btn_Star4->setFlat(false);
            ui->btn_Star5->setFlat(false);
            break;
        case 4:
            ui->btn_Star1->setFlat(true);
            ui->btn_Star2->setFlat(true);
            ui->btn_Star3->setFlat(true);
            ui->btn_Star4->setFlat(true);
            ui->btn_Star5->setFlat(false);
            break;
        case 5:
            ui->btn_Star1->setFlat(true);
            ui->btn_Star2->setFlat(true);
            ui->btn_Star3->setFlat(true);
            ui->btn_Star4->setFlat(true);
            ui->btn_Star5->setFlat(true);
            break;
    }
}
