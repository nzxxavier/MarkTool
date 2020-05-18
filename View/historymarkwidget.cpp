#include "historymarkwidget.h"
#include "ui_historymarkwidget.h"

HistoryMarkWidget::HistoryMarkWidget(QString markId, QString value, qint32 rowCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryMarkWidget)
{
    ui->setupUi(this);
    this->markId = markId;
    ui->pushButton->setText(value.mid(0,10));
    this->rowCount = rowCount;
}

HistoryMarkWidget::~HistoryMarkWidget()
{
    delete ui;
}

void HistoryMarkWidget::focused(bool focus)
{
    ui->pushButton->setFlat(focus);
}

qint32 HistoryMarkWidget::getRowCount()
{
    return this->rowCount;
}

void HistoryMarkWidget::on_pushButton_clicked()
{
    if (this->markId != NULL && this->markId != "")
    {
        emit historyMarkWidget_clicked(this->markId);
    }
}
