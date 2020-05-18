#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include "uuidcontroller.h"
#include "usercontroller.h"
#include "Model/user.h"
#include "Model/app.h"
#include "Model/comment.h"
#include "Model/mark.h"
#include "Model/correction.h"


class DataBaseController
{
public:
    //构造单例模式（懒汉单例模式）
    ~DataBaseController()
    {
       qDebug()<<"destructor called!";
    }

    DataBaseController(const DataBaseController&)=delete;
    DataBaseController& operator=(const DataBaseController&)=delete;

    static DataBaseController& getInstance(){
        static DataBaseController instance;
        instance.initConnection("127.0.0.1", "root", "nzx123", "marktool");
        return instance;
    }
    //初始化数据库连接
    bool initConnection(QString url, QString name, QString password, QString Database);

    QString lastError();

    bool insertUser(QString userName, QString userPassword);
    bool insertApp(QString userId, QString appName, QString appVer);
    bool insertOldApp(QString appId, QString userId, QString appName, QString appVer);
    QString insertComment(QString appName, QString commentTheme, QString commentContent, qint32 commentCreddit);
    bool insertOldComment(QString cmtId, QString appName, QString commentTheme, QString commentContent, qint32 commentCreddit);
    bool insertMark(QString userId, QString commentId, qint32 markClass, qint32 markCreddit, QString markContent, QString markNote);
    bool insertOldMark(QString markId, QString userId, QString commentId, qint32 markClass, qint32 markCreddit, QString markContent, QString markNote);
    bool insertCorrect(QString markId, qint32 markClass, qint32 markCreddit, QString markContent);
    bool insertOldCorrect(QString correctionId, QString markId, qint32 markClass, qint32 markCreddit, QString markContent);

    User* queryUser(QString value, User::queryType type);
    QList<App*> queryApp(QString value, App::queryType type);
    bool deleteApp(QString value, App::queryType type);
    QList<Comment*> queryComment(QString value, Comment::queryType type);
    QList<Mark*> queryMark(QString value, Mark::queryType type);
    QList<Mark*> queryMarkWithoutCorrect();
    QList<Correction*> queryCorrection(QString value, Correction::queryType type);

    bool isOpen()
    {
        return db.isOpen();
    }
private:
    DataBaseController(){
        qDebug()<<"constructor called!";
    }

    QSqlDatabase db;
    QString genUUID();
    QString genTime();
    bool execSQL(QString sql);
    QString error;
};

#endif // DATABASECONTROLLER_H
