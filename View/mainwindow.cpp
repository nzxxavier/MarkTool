#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        QCoreApplication::processEvents();
    } while (n.secsTo(now)<=2);//5为需要延时的秒数

    ui->setupUi(this);
    GetScreenInfo();
    this->resize(g_nActScreenX, g_nActScreenY);

    box = new MyMessageBox(this);
    correct = new CorrectWidget();
    data = new DataWidget();
    correct->setFixedSize(1000, 720);

    initSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginDialog;
    delete addAppDialog;
    delete dbConfigDialog;
    delete comment;
    delete correct;
    delete data;
    delete box;
}

void MainWindow::GetScreenInfo()
{
    QScreen* screen = QApplication::screens().first();

    //获取可用桌面大小
    QRect deskRect = screen->availableGeometry();
    //获取设备屏幕大小
    QRect screenRect = screen->geometry();

    g_nActScreenX = screenRect.width();
    g_nActScreenY = screenRect.height();

    //获取系统设置的屏幕个数（屏幕拷贝方式该值为1）
}

void MainWindow::initSignalSlots()
{
    connect(ui->loginAction, SIGNAL(triggered()), this, SLOT(on_ClickLoginAction()));
    connect(ui->addAppAction, SIGNAL(triggered()), this, SLOT(on_ClickAddAppAction()));
    connect(ui->databaseAction, SIGNAL(triggered()), this, SLOT(on_ClickDatabaseAction()));
    connect(ui->fileOutAction, SIGNAL(triggered()), this, SLOT(on_ClickFileOutAction()));
    connect(ui->fileInAction, SIGNAL(triggered()), this, SLOT(on_ClickFileInAction()));

    connect(this, SIGNAL(mainWindow_send_userId(QList<QList<QString>>*)), correct, SLOT(correct_receive_userId(QList<QList<QString>>*)));
    connect(this, SIGNAL(mainWindow_send_markId(QList<QList<QString>>*)), correct, SLOT(correct_receive_markId(QList<QList<QString>>*)));
    connect(this, SIGNAL(mainWindow_send_markCreddit(QList<QList<qint32>>*)), correct, SLOT(correct_receive_markCreddit(QList<QList<qint32>>*)));
    connect(this, SIGNAL(mainWindow_send_markClass(QList<QList<qint32>>*)), correct, SLOT(correct_receive_markClass(QList<QList<qint32>>*)));
    connect(this, SIGNAL(mainWindow_send_markContents(QList<QString>*)), correct, SLOT(correct_receive_markContents(QList<QString>*)));
}

void MainWindow::on_ClickLoginAction()
{
    loginDialog = new LoginDialog(this);

    //loginDialog->setModal(false);
    int result = loginDialog->exec();

    if(result == LoginDialog::Accepted)
    {
        ui->addAppAction->setEnabled(true);
        ui->fileInAction->setEnabled(true);
        ui->fileOutAction->setEnabled(true);
        ui->setAppStoreAction->setEnabled(true);
    }

    if(UserController::getInstance().isLogin())
    {
        loadContentByUserId();
    }
}

void MainWindow::on_ClickAddAppAction()
{
    addAppDialog = new AddAppDialog(this);

    addAppDialog->setModal(false);
    int result = addAppDialog->exec();

    if(result == AddAppDialog::Accepted)
    {
        reLoadContentByUserId();
    }
}

void MainWindow::on_ClickDatabaseAction()
{
    dbConfigDialog = new DBConfigDialog(this);

    dbConfigDialog->setModal(false);
    dbConfigDialog->show();
}

void MainWindow::on_ClickFileOutAction()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "./","EXCEL files(*.xls *.xlsx *.xlsm *.xlsb *.xltx);;All files (*.*)");
    if (fileName == "")
        return;
    FileController& fc = FileController::getInstance();
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QList<App*> apps = db.queryApp(uc.getFormalUser()->getUserId(), App::USER_ID);
    fc.startOutPut(fileName, apps);
    reLoadContentByUserId();
}

void MainWindow::on_ClickFileInAction()
{

    QString fileName = QFileDialog::getOpenFileName(this, "保存文件", "./","EXCEL files(*.xls *.xlsx *.xlsm *.xlsb *.xltx);;All files (*.*)");
    if (fileName == "")
        return;
    FileController& fc = FileController::getInstance();
    fc.startInPut(fileName);
    reLoadContentByUserId();
}

void MainWindow::loadContentByUserId()
{
    User* user = UserController::getInstance().getFormalUser();
    QList<App*> apps = DataBaseController::getInstance().queryApp(user->getUserId(), App::ALL);

    QFormLayout *pLayout = new QFormLayout();

    foreach (App* app, apps) {
        MyScrollWidget* widget;
        widget = new MyScrollWidget(this);
        widget->initValue(app->getAppName(), app->getAppVer(), app->getCMTNum(), app->getAppLasttime());
        pLayout->addRow(widget);
        connect(widget,SIGNAL(myscrollwidget_correct_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_correct(QString)));
        connect(widget,SIGNAL(myscrollwidget_delete_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_delete(QString)));
        connect(widget,SIGNAL(myscrollwidget_edit_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_edit(QString)));
        connect(widget,SIGNAL(myscrollwidget_data_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_data(QString)));

    }
    ui->scrollAreaWidgetContents->setLayout(pLayout);
}

void MainWindow::reLoadContentByUserId()
{
    User* user = UserController::getInstance().getFormalUser();
    QList<App*> apps = DataBaseController::getInstance().queryApp(user->getUserId(), App::ALL);

    QFormLayout *pLayout = (QFormLayout*)ui->scrollAreaWidgetContents->layout();
    while(!pLayout->isEmpty())
    {
        pLayout->removeRow(0);
    }

    foreach (App* app, apps) {
        MyScrollWidget* widget;
        widget = new MyScrollWidget(this);
        connect(widget,SIGNAL(myscrollwidget_correct_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_correct(QString)));
        widget->initValue(app->getAppName(), app->getAppVer(), app->getCMTNum(), app->getAppLasttime());
        pLayout->addRow(widget);
        connect(widget,SIGNAL(myscrollwidget_delete_clicked(QString)),this,SLOT(mainwindow_receive_myscrollwidget_delete(QString)));
        connect(widget,SIGNAL(myscrollwidget_edit_clicked(QString)),this, SLOT(mainwindow_receive_myscrollwidget_edit(QString)));
    }
    ui->scrollAreaWidgetContents->setLayout(pLayout);
}

void MainWindow::sendMessageToCorrect()
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();

    QList<Mark*> marks = db.queryMarkWithoutCorrect();

    qint32 markLen = marks.size();
    QList<QList<qint32>> res;


    bool markVisited[markLen];
    for (int i = 0; i < markLen; i ++) markVisited[i] = false;
    for (qint32 i = 0; i < markLen; i ++)
    {
        if (markVisited[i] == true) continue;

        markVisited[i] = true;
        bool isRepeat = false;
        QList<qint32> res_list;
        res_list.append(i);

        if (marks[i]->getMarkCredit() <= 3) isRepeat = true;

        for (int j = i + 1; j < markLen; j ++)
        {
            if (markVisited[j] == true) continue;
            if (marks[i]->getMarkContent() == marks[j]->getMarkContent())
            {
                isRepeat = true;
                markVisited[j] = true;
                res_list.append(j);
            }
        }
        if (isRepeat)
            res.append(res_list);
    }
    qint32 len = res.size();

    QList<QList<QString>>* markId = new QList<QList<QString>>();
    QList<QList<QString>>* userId = new QList<QList<QString>>();
    QList<QList<qint32>>* markClass = new QList<QList<qint32>>();
    QList<QList<qint32>>* markCreddit = new QList<QList<qint32>>();
    QList<QString>* markContents = new QList<QString>();

    for (qint32 i = 0; i < len; i ++)
    {
        QList<QString> mark_list;
        QList<QString> user_list;
        QList<qint32> class_list;
        QList<qint32> creddit_list;
        for (qint32 j = 0; j < res[i].size(); j ++)
        {
            mark_list.append(marks[res[i][j]]->getMarkId());
            user_list.append(marks[res[i][j]]->getUserId());
            class_list.append(marks[res[i][j]]->getMarkClass());
            creddit_list.append(marks[res[i][j]]->getMarkCredit());
        }
        markId->append(mark_list);
        userId->append(user_list);
        markClass->append(class_list);
        markCreddit->append(creddit_list);
        markContents->append(marks[res[i][0]]->getMarkContent());
    }
    emit mainWindow_send_markId(markId);
    emit mainWindow_send_userId(userId);
    emit mainWindow_send_markClass(markClass);
    emit mainWindow_send_markCreddit(markCreddit);
    emit mainWindow_send_markContents(markContents);
}

void MainWindow::mainwindow_receive_myscrollwidget_delete(QString appName)
{    
    DataBaseController& db = DataBaseController::getInstance();
    box->init(1,"删除应用","确认删除这个应用么？");
    box->exec();
    if(box->getResult() == 1){
        db.deleteApp(appName, App::APP_NAME);
        reLoadContentByUserId();
    }
}

void MainWindow::mainwindow_receive_myscrollwidget_edit(QString appName)
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    comment = new CommentWidget();

    QString app_id = db.queryApp(appName, App::APP_NAME).first()->getAppId();
    QList<Comment*> comments = db.queryComment(app_id, Comment::APP_ID);
    if(comments.length() == 0)
    {
        box->init(0, "无可用评论", "请导入评论");
        box->exec();
        return;
    }
    uc.setCommentPool(db.queryComment(app_id, Comment::APP_ID));
    uc.setCommentCount(0);

    comment->initValue(appName, QString::number(comments.first()->getCmtCreddit()), comments.first()->getCmtTheme(), comments.first()->getCmtContent(), uc.getCommentCount() + 1, comments.size());
    comment->show();
}

void MainWindow::mainwindow_receive_myscrollwidget_correct(QString appName)
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QString app_id = db.queryApp(appName, App::APP_NAME).first()->getAppId();
    QList<Comment*> comments = db.queryComment(app_id, Comment::APP_ID);
    if(comments.length() == 0)
    {
        box->init(0, "无可用评论", "请导入评论");
        box->exec();
        return;
    }
    uc.setCommentPool(db.queryComment(app_id, Comment::APP_ID));
    uc.setCommentCount(0);

    sendMessageToCorrect();
    correct->reLoad();
    correct->show();
}

void MainWindow::mainwindow_receive_myscrollwidget_data(QString appName)
{
    DataBaseController& db = DataBaseController::getInstance();
    UserController& uc = UserController::getInstance();
    QString app_id = db.queryApp(appName, App::APP_NAME).first()->getAppId();
    QList<Comment*> comments = db.queryComment(app_id, Comment::APP_ID);
    if(comments.length() == 0)
    {
        box->init(0, "无可用评论", "请导入评论");
        box->exec();
        return;
    }
    data->show();
}
