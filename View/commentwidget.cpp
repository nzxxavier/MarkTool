#include "commentwidget.h"

CommentWidget::CommentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentWidget)
{
    ui->setupUi(this);
    this->setFixedSize(640, 720);
    this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    box = new MyMessageBox(this);
    mark = new MarkWidget(this);
    mark->move(this->geometry().width() + 5,0);
    mark->setVisible(false);
    connect(this,SIGNAL(comment_send_commentId(QString)),mark,SLOT(mark_receive_commentId(QString)));
}

CommentWidget::~CommentWidget()
{
    delete ui;
    delete mark;
    delete box;
}

void CommentWidget::initValue(QString appName, QString appValue, QString cmtTheme, QString comment, qint32 current, qint32 max)
{
    ui->label_AppNameDisplay->setText(appName);
    ui->label_AppValueDiaplay->setText(appValue);
    ui->label_CMTThemeDisplay->setText(cmtTheme);
    ui->textBrowser_Comment->setText(comment);
    ui->progressBar->setRange(0, max);
    ui->progressBar->setValue(current);
    ui->btn_Last->setEnabled(false);
}

void CommentWidget::on_btn_Next_clicked()
{
    UserController& uc = UserController::getInstance();
    uc.setCommentCount(uc.getCommentCount() + 1);
    Comment* comment = uc.getCommentPool().at(uc.getCommentCount());

    if(uc.getCommentCount() == 0)
    {
        ui->btn_Last->setEnabled(false);
    }
    else if(uc.getCommentCount() == uc.getCommentPool().length() - 1)
    {
        ui->btn_Next->setEnabled(false);
    }
    else
    {
        ui->btn_Last->setEnabled(true);
    }

    ui->label_AppValueDiaplay->setText(QString::number(comment->getCmtCreddit()));
    ui->label_CMTThemeDisplay->setText(comment->getCmtTheme());
    ui->textBrowser_Comment->setText(comment->getCmtContent());
    ui->progressBar->setValue(uc.getCommentCount() + 1);

    if(mark->isVisible())
    {
        UserController& uc = UserController::getInstance();
        emit comment_send_commentId(uc.getCommentPool().at(uc.getCommentCount())->getCmtID());
        mark->reLoad();
    }
}

void CommentWidget::on_btn_Last_clicked()
{
    UserController& uc = UserController::getInstance();
    uc.setCommentCount(uc.getCommentCount() - 1);
    Comment* comment = uc.getCommentPool().at(uc.getCommentCount());

    if(uc.getCommentCount() == 0 )
    {
        ui->btn_Last->setEnabled(false);
    }
    else if(uc.getCommentCount() == uc.getCommentPool().length() - 1)
    {
        ui->btn_Next->setEnabled(false);
    }
    else
    {
        ui->btn_Next->setEnabled(true);
    }

    ui->label_AppValueDiaplay->setText(QString::number(comment->getCmtCreddit()));
    ui->label_CMTThemeDisplay->setText(comment->getCmtTheme());
    ui->textBrowser_Comment->setText(comment->getCmtContent());
    ui->progressBar->setValue(uc.getCommentCount() + 1);

    if(mark->isVisible())
    {
        UserController& uc = UserController::getInstance();
        emit comment_send_commentId(uc.getCommentPool().at(uc.getCommentCount())->getCmtID());
        mark->reLoad();
    }
}

void CommentWidget::on_toolButton_clicked()
{
    if (this->mark->isVisible())
    {
        closeMark();
    }
    else
    {
        openMark();
    }
}

void CommentWidget::openMark()
{
    UserController& uc = UserController::getInstance();
    this->setFixedSize(this->geometry().width() + mark->geometry().width(), this->geometry().height());
    this->move(this->geometry().x() - mark->geometry().width() / 2, (QApplication::desktop()->height() - this->height()) / 2);
    emit comment_send_commentId(uc.getCommentPool().at(uc.getCommentCount())->getCmtID());
    mark->show();
    mark->reLoad();
}


void CommentWidget::closeMark()
{
    this->setFixedSize(this->geometry().width() - mark->geometry().width(), this->geometry().height());
    this->move(this->geometry().x() + mark->geometry().width() / 2, (QApplication::desktop()->height() - this->height()) / 2);
    mark->close();
}

void CommentWidget::on_btn_Note_clicked()
{
    DataBaseController &db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();

    qint32 markClass = mark->getMarkClass();
    if (markClass == -1)
    {
        box->init(0, "标记失败", "请选择标记类别！");
        box->exec();
        return;
    }

    qint32 markCreddit = mark->getMarkCreddit();
    if (markCreddit == 0)
    {
        box->init(0, "标记失败", "请选择置信度！");
        box->exec();
        return;
    }

    QTextCursor cursor = ui->textBrowser_Comment->textCursor();
    QTextDocumentFragment f = cursor.selection();
    QString markContent = f.toPlainText();

    if (markContent == "")
    {
        box->init(0, "标记失败", "请选择标注内容！");
        box->exec();
        return;
    }

    if (!db.insertMark(uc.getFormalUser()->getUserId(), uc.getCommentPool().at(uc.getCommentCount())->getCmtID(), markClass, markCreddit, markContent, mark->getMarkNote()))
    {
        box->init(0, "标记失败", db.lastError());
        box->exec();
        return;
    }

    mark->reLoad();
}
