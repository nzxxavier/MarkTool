#include "historymarkwidget.h"
#include "ui_historymarkwidget.h"

HistoryMarkWidget::HistoryMarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryMarkWidget)
{
    ui->setupUi(this);
}

HistoryMarkWidget::~HistoryMarkWidget()
{
    delete ui;
}
