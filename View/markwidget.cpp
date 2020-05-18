#include "markwidget.h"
#include "ui_markwidget.h"

MarkWidget::MarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkWidget)
{
    ui->setupUi(this);
}

MarkWidget::~MarkWidget()
{
    delete ui;
}
