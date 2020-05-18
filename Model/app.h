#ifndef APP_H
#define APP_H
#include <QString>


class App
{
public:
    App();
    App(QString appId = "", QString userId = "", QString appName = "", QString appLasttime = "", QString appVer = "", qint32 cmtNum = 0);

    QString getAppId();
    QString getUserId();
    QString getAppName();
    QString getAppLasttime();
    QString getAppVer();
    qint32 getCMTNum();

    void setAppId(QString appId);
    void setUserId(QString userId);
    void setAppName(QString appName);
    void setAppLasttime(QString appLasttime);
    void setAppVer(QString appVer);
    void setCMTNum(qint32 cmtNum);

    enum queryType
    {
        APP_ID,
        USER_ID,
        APP_NAME,
        ALL
    };
private:
    QString appId;
    QString userId;
    QString appName;
    QString appLasttime;
    QString appVer;
    qint32 cmtNum;
};

#endif // APP_H
