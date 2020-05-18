#include "correctwidget.h"
#include "ui_correctwidget.h"

CorrectWidget::CorrectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectWidget)
{
    ui->setupUi(this);
}

CorrectWidget::~CorrectWidget()
{
    delete ui;
}
