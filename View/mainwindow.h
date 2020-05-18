 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <View/logindialog.h>
#include <View/addappdialog.h>
#include <View/dbconfigdialog.h>
#include <View/myscrollwidget.h>
#include <View/commentwidget.h>
#include <View/mymessagebox.h>
#include <View/datawidget.h>
#include <QScreen>
#include <QList>
#include <QRect>
#include <QFormLayout>
#include <QFileDialog>
#include <Controller/filecontroller.h>
#include <Controller/databasecontroller.h>
#include <Controller/usercontroller.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void mainwindow_receive_myscrollwidget_delete(QString appName);
    void mainwindow_receive_myscrollwidget_edit(QString appName);
    void mainwindow_receive_myscrollwidget_correct(QString appName);
    void mainwindow_receive_myscrollwidget_data(QString appName);
private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    AddAppDialog *addAppDialog;
    DBConfigDialog *dbConfigDialog;
    CommentWidget *comment;
    CorrectWidget *correct;
    DataWidget *data;
    MyMessageBox* box;

    qint32 g_nActScreenX;
    qint32 g_nActScreenY;
    qint32 g_nScreenCount;

    void GetScreenInfo();
    void initSignalSlots();
    void loadContentByUserId();
    void reLoadContentByUserId();
    void sendMessageToCorrect();

private slots:
    void on_ClickLoginAction();
    void on_ClickAddAppAction();
    void on_ClickDatabaseAction();
    void on_ClickFileOutAction();
    void on_ClickFileInAction();

signals:
    void mainWindow_send_userId(QList<QList<QString>>* userId);
    void mainWindow_send_markId(QList<QList<QString>>* markId);
    void mainWindow_send_markClass(QList<QList<qint32>>* markClass);
    void mainWindow_send_markCreddit(QList<QList<qint32>>* markCreddit);
    void mainWindow_send_markContents(QList<QString>* markContents);


};
#endif // MAINWINDOW_H
