#include "markwidget.h"
#include "ui_markwidget.h"

MarkWidget::MarkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    ui->scrollArea->setLayout(new QFormLayout());
    hide();
}

MarkWidget::~MarkWidget()
{
    delete ui;
}

void MarkWidget::on_btn_Star1_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(false);
    ui->btn_Star3->setFlat(false);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
}

void MarkWidget::on_btn_Star2_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(false);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
}

void MarkWidget::on_btn_Star3_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(false);
    ui->btn_Star5->setFlat(false);
}

void MarkWidget::on_btn_Star4_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(true);
    ui->btn_Star5->setFlat(false);
}

void MarkWidget::on_btn_Star5_clicked()
{
    ui->btn_Star1->setFlat(true);
    ui->btn_Star2->setFlat(true);
    ui->btn_Star3->setFlat(true);
    ui->btn_Star4->setFlat(true);
    ui->btn_Star5->setFlat(true);
}

qint32 MarkWidget::getMarkClass()
{
    return markClass;
}

qint32 MarkWidget::getMarkCreddit()
{
    if (ui->btn_Star5->isFlat())
        return 5;
    else if (ui->btn_Star4->isFlat())
        return 4;
    else if (ui->btn_Star3->isFlat())
        return 3;
    else if (ui->btn_Star2->isFlat())
        return 2;
    else if (ui->btn_Star1->isFlat())
        return 1;
    else
        return 0;
}

QString MarkWidget::getMarkNote()
{
    return ui->plainTextEdit->toPlainText();
}

void MarkWidget::reLoad()
{
    clean();
    ui->plainTextEdit->setPlainText("");

    if (commentId != "" && commentId != NULL)
    {
        DataBaseController& db = DataBaseController::getInstance();
        QList<Mark*> marks = db.queryMark(this->commentId, Mark::COMMENT_ID);

        QFormLayout *pLayout = (QFormLayout*)ui->scrollArea->layout();

        while (!pLayout->isEmpty())
        {
            pLayout->removeRow(0);
        }

        for (int i = 0; i < marks.length(); i ++)
        {
            HistoryMarkWidget* his = new HistoryMarkWidget(marks.at(i)->getMarkId(),marks.at(i)->getAddTime(), i);
            pLayout->addRow(his);
            connect(his, SIGNAL(historyMarkWidget_clicked(QString)), this, SLOT(mark_receive_markId(QString)));
        }
        ui->scrollArea->setLayout(pLayout);
    }

}

void MarkWidget::on_btn_Type1_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.功能完整性：功能集涵盖所有指定任务和用户目标的程度。\n"
                           "2.功能正确性：功能集可以提供所需精度的正确结果的程度。\n"
                           "3.功能适当性：功能集便于完成特定任务和目标的程度。");
    if (checked)
    {
        markClass = Mark::FEATURE;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}


void MarkWidget::on_btn_Type2_toggled(bool checked)
{
    if (checked)
    {
        markClass = Mark::NONFEATURE;
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type3_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.时间表现：产品或系统在执行其功能时，其响应和处理时间以及吞吐率达到要求的程度。\n"
                           "2.资源利用率：产品或系统在执行其功能时使用的资源数量和类型满足要求的程度。\n"
                           "3.容量：产品或系统的最大限制和参数满足要求的程度。");
    if (checked)
    {
        markClass = Mark::PERFORMANCE;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type4_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.共存性：产品在与其他产品共享公共环境和资源的同时能够有效执行其所需功能的程度，而不会对任何其他产品造成不利影响。\n"
                           "2.互通性：两个或更多系统，产品或组件可以交换信息并使用已交换的信息的程度。");
    if (checked)
    {
        markClass = Mark::COMPATIBILITY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type5_toggled(bool checked)
{

    QString text = QString("需参考：\n"
                           "1.适当性的可识别性：用户可以识别产品或系统是否适合其需求的程度。\n"
                           "2.可学习性：产品或系统使用户能够学习如何在紧急情况下有效，高效地使用产品的程度。\n"
                           "3.可操作性：产品或系统易于操作，控制和适当使用的程度。\n"
                           "4.用户错误保护：产品或系统保护用户避免错误的程度。\n"
                           "5.用户界面美观度：用户界面为用户带来令人愉悦和令人满意的交互的程度。\n"
                           "6.可访问性：具有最大范围的特性和能力的人员可以在特定的使用上下文中使用产品或系统以达到特定目标的程度");
    if (checked)
    {
        markClass = Mark::USABILITY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type6_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.成熟度：系统、产品或组件在正常操作下满足可靠性需求的程度。\n"
                           "2.可用性：产品或系统在需要使用时可操作和可访问的程度。\n"
                           "3.容错能力：出现硬件或软件故障时，系统、产品或组件按预期运行的程度。\n"
                           "4.可恢复性：在发生中断或故障时，产品或系统可以恢复直接受影响的数据并重新建立系统所需状态的程度。");
    if (checked)
    {
        markClass = Mark::RELIABILITY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type7_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.机密性：原型在何种程度上确保只有授权访问的人才能访问数据。\n"
                           "2.完整性：系统，产品或组件防止未经授权访问或修改计算机程序或数据的行为的程度。\n"
                           "3.不可抵赖性：可以证明已发生的动作或事件的程度，因此这些事件或动作以后无法被抵销。\n"
                           "4.问责制：可以将实体的行为唯一地追溯到实体的程度。\n"
                           "5.真实性：主题或资源的身份可被证明是所主张的程度。");
    if (checked)
    {
        markClass = Mark::SAFETY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type8_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.模块化：系统或计算机程序由离散组件组成的程度，以使对一个组件的更改对其他组件的影响最小。\n"
                           "2.可重用性：资产在多个系统中或在构建其他资产中的使用程度。\n"
                           "3.可分析性：有效性和效率的程度，可以用来评估一个或多个零件的预期变更对产品或系统的影响，或诊断产品的缺陷或故障原因，或识别零件是否被修改。\n"
                           "4.可修改性：在不引入缺陷或不降低现有产品质量的情况下，可以有效，高效地修改产品或系统的程度。\n"
                           "5.可测试性：可以为系统，产品或组件建立测试标准并进行测试以确定是否满足这些标准的有效性和效率程度。");
    if (checked)
    {
        markClass = Mark::MAINTAINABILITY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type9_toggled(bool checked)
{
    QString text = QString("需参考：\n"
                           "1.适应性：产品或系统可以有效和高效地适应不同或不断发展的硬件，软件或其他操作或使用环境的程度。\n"
                           "2.可安装性：在指定环境中可以成功安装或卸载产品或系统的有效性和效率。\n"
                           "3.可替换性：同一环境中，同一目的产品可以替换另一指定软件产品的程度。");
    if (checked)
    {
        markClass = Mark::PORTABILITY;
        ui->textBrowser_explain->setText(text);
    }
    else
        markClass = 0;
}

void MarkWidget::on_btn_Type10_toggled(bool checked)
{
    if (checked)
    {
        markClass = Mark::OTHER;
    }
    else
        markClass = 0;
}

void MarkWidget::mark_receive_commentId(QString commentId)
{
    this->commentId = commentId;
}

void MarkWidget::mark_receive_markId(QString markId)
{
    DataBaseController& db = DataBaseController::getInstance();
    Mark* mark = db.queryMark(markId, Mark::MARK_ID).first();
    clean();
    switch (mark->getMarkClass()) {
        case 1:ui->btn_Type1->setChecked(true); break;
        case 2:ui->btn_Type2->setChecked(true); break;
        case 3:ui->btn_Type3->setChecked(true); break;
        case 4:ui->btn_Type4->setChecked(true); break;
        case 5:ui->btn_Type5->setChecked(true); break;
        case 6:ui->btn_Type6->setChecked(true); break;
        case 7:ui->btn_Type7->setChecked(true); break;
        case 8:ui->btn_Type8->setChecked(true); break;
        case 9:ui->btn_Type9->setChecked(true); break;
        case 10:ui->btn_Type10->setChecked(true); break;
    }
    switch (mark->getMarkCredit()) {
        case 1:on_btn_Star1_clicked(); break;
        case 2:on_btn_Star2_clicked(); break;
        case 3:on_btn_Star3_clicked(); break;
        case 4:on_btn_Star4_clicked(); break;
        case 5:on_btn_Star5_clicked(); break;
    }
    ui->plainTextEdit->setPlainText(mark->getMarkNode());
    QFormLayout* layout = (QFormLayout*) ui->scrollArea->layout();
    qint32 len = layout->rowCount();
    for(int i = 0; i < len; i ++)
    {
        HistoryMarkWidget* his = (HistoryMarkWidget*)layout->itemAt(i)->widget();
        qint32 rowCount = his->getRowCount();
        i == rowCount ? his->focused(true) : his->focused(false);
    }
}

void MarkWidget::clean()
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
    ui->textBrowser_explain->setText("");
}
