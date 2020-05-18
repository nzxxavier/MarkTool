#include "datawidget.h"
#include "ui_datawidget.h"

DataWidget::DataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataWidget)
{
    ui->setupUi(this);
    QChart* chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    ui->widget_chart->setChart(chart);
    box = new MyMessageBox(this);
    this->hide();
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::on_btn_Creddit_clicked()
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QList<Mark*> marks = db.queryMark(uc.getFormalUser()->getUserId(), Mark::USER_ID);
    qint32 values[5];
    for (qint32 i = 0; i < 5; i ++) {
        values[i] = 0;
    }
    qint32 len = marks.size();

    if(len == 0)
    {
        box->init(0, "无可用标注", "请标注");
        box->exec();
        return;
    }
    for (qint32 i = 0; i < len; i ++) {
        qint32 markCreddit = marks.at(i)->getMarkCredit();
        values[markCreddit - 1] ++;
    }

    QPieSeries* pie = new QPieSeries();
    QPieSlice *slice1 = new QPieSlice(QString("置信度1"), values[0]);
    slice1->setLabelVisible(true);
    slice1->setLabelColor(Qt::white);
    slice1->setLabel(QString("置信度1：%1").arg(values[0]));
    slice1->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice1);

    QPieSlice *slice2 = new QPieSlice(QString("置信度2"), values[1]);
    slice2->setLabelVisible(true);
    slice2->setLabelColor(Qt::white);
    slice2->setLabel(QString("置信度2：%1").arg(values[1]));
    slice2->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice2);

    QPieSlice *slice3 = new QPieSlice(QString("置信度3"), values[2]);
    slice3->setLabelVisible(true);
    slice3->setLabelColor(Qt::white);
    slice3->setLabel(QString("置信度3：%1").arg(values[2]));
    slice3->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice3);

    QPieSlice *slice4 = new QPieSlice(QString("置信度4"), values[3]);
    slice4->setLabelVisible(true);
    slice4->setLabelColor(Qt::white);
    slice4->setLabel(QString("置信度4：%1").arg(values[3]));
    slice4->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice4);

    QPieSlice *slice5 = new QPieSlice(QString("置信度5"), values[4]);
    slice5->setLabelVisible(true);
    slice5->setLabelColor(Qt::white);
    slice5->setLabel(QString("置信度5：%1").arg(values[4]));
    slice5->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice5);

    QChart* chart = new QChart();
    chart->addSeries(pie);
    chart->setTitle("置信度分布");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("微软雅黑",12));
    ui->widget_chart->setChart(chart);
}

void DataWidget::on_btn_Class_clicked()
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QList<Mark*> marks = db.queryMark(uc.getFormalUser()->getUserId(), Mark::USER_ID);
    qint32 values[10];
    for (qint32 i = 0; i < 10; i ++) {
        values[i] = 0;
    }
    qint32 len = marks.size();
    for (qint32 i = 0; i < len; i ++) {
        qint32 markClass = marks.at(i)->getMarkClass();
        values[markClass - 1] ++;
    }

    QPieSeries* pie = new QPieSeries();
    QPieSlice *slice1 = new QPieSlice(QString("功能性需求"), values[0]);
    slice1->setLabelVisible(true);
    slice1->setLabelColor(Qt::white);
    slice1->setLabel(QString("功能性需求：%1").arg(values[0]));
    slice1->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice1);

    qint32 nfr_value = 0;
    for (qint32 i = 1; i < 9; i ++)
    {
        nfr_value += values[i];
    }

    QPieSlice *slice2 = new QPieSlice(QString("非功能性需求"), nfr_value);
    slice2->setLabelVisible(true);
    slice2->setLabelColor(Qt::white);
    slice2->setLabel(QString("功能性需求：%1").arg(nfr_value));
    slice2->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice2);

    QPieSlice *slice3 = new QPieSlice(QString("其他"), values[9]);
    slice3->setLabelVisible(true);
    slice3->setLabelColor(Qt::white);
    slice3->setLabel(QString("其他：%1").arg(values[9]));
    slice3->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice3);

    QChart* chart = new QChart();
    chart->addSeries(pie);
    chart->setTitle("标注类型分布");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("微软雅黑",12));
    ui->widget_chart->setChart(chart);
}

void DataWidget::on_btn_Correct_clicked()
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QList<Mark*> marks = db.queryMark(uc.getFormalUser()->getUserId(), Mark::USER_ID);
    qint32 values[10];
    for (qint32 i = 0; i < 10; i ++) {
        values[i] = 0;
    }
    qint32 len = marks.size();
    for (qint32 i = 0; i < len; i ++) {
        qint32 markClass = marks.at(i)->getMarkClass();
        values[markClass - 1] ++;
    }

    QPieSeries* pie = new QPieSeries();

    QPieSlice *slice1 = new QPieSlice(QString("性能"), values[2]);
    slice1->setLabelVisible(true);
    slice1->setLabelColor(Qt::white);
    slice1->setLabel(QString("性能：%1").arg(values[2]));
    slice1->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice1);

    QPieSlice *slice2 = new QPieSlice(QString("兼容性"), values[3]);
    slice2->setLabelVisible(true);
    slice2->setLabelColor(Qt::white);
    slice2->setLabel(QString("兼容性：%1").arg(values[3]));
    slice2->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice2);

    QPieSlice *slice3 = new QPieSlice(QString("可用性"), values[4]);
    slice3->setLabelVisible(true);
    slice3->setLabelColor(Qt::white);
    slice3->setLabel(QString("可用性：%1").arg(values[4]));
    slice3->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice3);

    QPieSlice *slice4 = new QPieSlice(QString("可靠性"), values[5]);
    slice4->setLabelVisible(true);
    slice4->setLabelColor(Qt::white);
    slice4->setLabel(QString("可靠性：%1").arg(values[5]));
    slice4->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice4);

    QPieSlice *slice5 = new QPieSlice(QString("安全性"), values[6]);
    slice5->setLabelVisible(true);
    slice5->setLabelColor(Qt::white);
    slice5->setLabel(QString("安全性：%1").arg(values[6]));
    slice5->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice5);

    QPieSlice *slice6 = new QPieSlice(QString("可维护性"), values[7]);
    slice6->setLabelVisible(true);
    slice6->setLabelColor(Qt::white);
    slice6->setLabel(QString("可维护性：%1").arg(values[7]));
    slice6->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice6);

    QPieSlice *slice7 = new QPieSlice(QString("可移植性"), values[8]);
    slice7->setLabelVisible(true);
    slice7->setLabelColor(Qt::white);
    slice7->setLabel(QString("可移植性：%1").arg(values[8]));
    slice7->setLabelPosition(QPieSlice::LabelOutside);
    pie->append(slice7);

    QChart* chart = new QChart();
    chart->addSeries(pie);
    chart->setTitle("NFR类型分布");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("微软雅黑",12));
    ui->widget_chart->setChart(chart);
}
