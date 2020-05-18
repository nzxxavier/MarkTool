#include "tocorrectwidget.h"
#include "ui_tocorrectwidget.h"

ToCorrectWidget::ToCorrectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToCorrectWidget)
{
    ui->setupUi(this);
}

ToCorrectWidget::~ToCorrectWidget()
{
    delete ui;
}
