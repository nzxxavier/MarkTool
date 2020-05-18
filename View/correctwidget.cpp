#include "correctwidget.h"
#include "ui_correctwidget.h"

CorrectWidget::CorrectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectWidget)
{
    ui->setupUi(this);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    box = new MyMessageBox(this);
    QFormLayout* pLayout = new QFormLayout();
    pLayout->setMargin(0);
    pLayout->setSpacing(3);
    ui->scrollArea->setLayout(pLayout);
    ui->btn_Last->setEnabled(false);
}

CorrectWidget::~CorrectWidget()
{
    delete ui;
    delete userId;
    delete markId;
    delete markContent;
    delete markClass;
    delete markCreddit;
}

void CorrectWidget::on_btn_Star1_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(false);
    ui->btn_Star3->setFlat(false);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
    this->correctCreddit = 1;
}

void CorrectWidget::on_btn_Star2_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(false);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
    this->correctCreddit = 2;
}

void CorrectWidget::on_btn_Star3_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
    this->correctCreddit = 3;
}

void CorrectWidget::on_btn_Star4_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(true);
    ui->btn_Star5->setFlat(false);
    this->correctCreddit = 4;
}

void CorrectWidget::on_btn_Star5_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(true);
    ui->btn_Star5->setFlat(true);
    this->correctCreddit = 5;
}

void CorrectWidget::on_btn_Type1_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 1;
    }
}

void CorrectWidget::on_btn_Type2_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 2;
    }
}

void CorrectWidget::on_btn_Type3_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 3;
    }
}

void CorrectWidget::on_btn_Type4_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 4;
    }
}

void CorrectWidget::on_btn_Type5_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 5;
    }
}

void CorrectWidget::on_btn_Type6_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 6;
    }
}

void CorrectWidget::on_btn_Type7_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 7;
    }
}

void CorrectWidget::on_btn_Type8_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 8;
    }
}

void CorrectWidget::on_btn_Type9_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 9;
    }
}

void CorrectWidget::on_btn_Type10_toggled(bool checked)
{
    if (checked == true)
    {
        this->correctType = 10;
    }
}



void CorrectWidget::on_btn_Submit_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();

    qint32 markClass = this->getMarkClass();
    if (markClass == -1)
    {
        box->init(0, "标记失败", "请选择标记类别！");
        box->exec();
        return;
    }

    qint32 markCreddit = this->getMarkCreddit();
    if (markCreddit == 0)
    {
        box->init(0, "标记失败", "请选择置信度！");
        box->exec();
        return;
    }

    qint32 len = markId->at(currentCount).size();
    bool isInserted = true;

    for (qint32 i = 0; i < len; i ++)
    {
        if(!db.insertCorrect(markId->at(currentCount).at(i), getMarkClass(),
                             getMarkCreddit(), ui->textBrowser->toPlainText())) isInserted = false;
    }

    if (isInserted == true)
    {
        this->markId->removeAt(currentCount);
        this->userId->removeAt(currentCount);
        this->markClass->removeAt(currentCount);
        this->markCreddit->removeAt(currentCount);
    }
    else
    {
        box->init(0, "保存审阅失败", db.lastError());
        box->exec();
        qDebug() << db.lastError();
    }
    currentCount = 0;

    this->reLoad();
}

void CorrectWidget::correct_receive_userId(QList<QList<QString>>* userId)
{
    this->userId = userId;
}

void CorrectWidget::correct_receive_markId(QList<QList<QString>>* markId)
{
    this->markId = markId;
}

void CorrectWidget::correct_receive_markContents(QList<QString>* markContent)
{
    this->markContent = markContent;
}

void CorrectWidget::correct_receive_markClass(QList<QList<qint32>>* markClass)
{
    this->markClass = markClass;
}

void CorrectWidget::correct_receive_markCreddit(QList<QList<qint32>>* markCreddit)
{
    this->markCreddit = markCreddit;
}

QRadioButton* CorrectWidget::chooseTypeButton(qint32 type)
{
    switch(type){
    case 1:
        return ui->btn_Type1;
    case 2:
        return ui->btn_Type2;
    case 3:
        return ui->btn_Type3;
    case 4:
        return ui->btn_Type4;
    case 5:
        return ui->btn_Type5;
    case 6:
        return ui->btn_Type6;
    case 7:
        return ui->btn_Type7;
    case 8:
        return ui->btn_Type8;
    case 9:
        return ui->btn_Type9;
    case 10:
        return ui->btn_Type10;
    }
}

void CorrectWidget::reLoad()
{
    DataBaseController& db = DataBaseController::getInstance();
    clean();
    qint32 len = userId->at(currentCount).size();
    if (len < 1)
    {
        ui->btn_Submit->setEnabled(false);
        return;
    }

    QFormLayout *pLayout = (QFormLayout*)ui->scrollArea->layout();

    for (qint32 i = 0; i < len; i ++)
    {
        QString userName = db.queryUser(this->userId->at(currentCount).at(i), User::USER_ID)->getUserName();
        qint32 markClass = this->markClass->at(currentCount).at(i);
        qint32 markCreddit = this->markCreddit->at(currentCount).at(i);
        ToCorrectWidget* tc = new ToCorrectWidget(userName, markClass, markCreddit);
        pLayout->addRow(tc);
    }

    ui->textBrowser->setText(markContent->at(currentCount));
    ui->progressBar->setRange(0, markId->size());
    ui->progressBar->setValue(currentCount + 1);
}

void CorrectWidget::clean()
{
    ui->btn_Star1->setFlat(false);
    ui->btn_Star2->setFlat(false);
    ui->btn_Star3->setFlat(false);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
    ui->btn_Type1->setChecked(false);
    ui->btn_Type2->setChecked(false);
    ui->btn_Type3->setChecked(false);
    ui->btn_Type4->setChecked(false);
    ui->btn_Type5->setChecked(false);
    ui->btn_Type6->setChecked(false);
    ui->btn_Type7->setChecked(false);
    ui->btn_Type8->setChecked(false);
    ui->btn_Type9->setChecked(false);
    ui->btn_Type10->setChecked(false);
    ui->btn_Submit->setEnabled(true);
    QFormLayout *pLayout = (QFormLayout*)ui->scrollArea->layout();
    while (!pLayout->isEmpty())
    {
        pLayout->removeRow(0);
    }
    ui->textBrowser->setText("");
}

qint32 CorrectWidget::getMarkClass()
{
    return this->correctType;
}

qint32 CorrectWidget::getMarkCreddit()
{
    return this->correctCreddit;
}

void CorrectWidget::on_btn_Last_clicked()
{
    currentCount --;
    if(currentCount == -1)
    {
        ui->btn_Next->setEnabled(true);
        ui->btn_Last->setEnabled(false);
        currentCount --;
    }
    if(currentCount == 0)
    {
        ui->btn_Next->setEnabled(true);
        ui->btn_Last->setEnabled(false);
        reLoad();
    }
    else
    {
        ui->btn_Next->setEnabled(true);
        reLoad();
    }
}

void CorrectWidget::on_btn_Next_clicked()
{
    currentCount ++;
    if(currentCount == markId->size())
    {
        ui->btn_Next->setEnabled(false);
        ui->btn_Last->setEnabled(true);
        currentCount --;
    }
    else if(currentCount == markId->size() - 1)
    {
        ui->btn_Next->setEnabled(false);
        ui->btn_Last->setEnabled(true);
        reLoad();
    }
    else
    {
        ui->btn_Last->setEnabled(true);
        reLoad();
    }

}
