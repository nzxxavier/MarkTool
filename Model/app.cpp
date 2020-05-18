#include "app.h"

App::App()
{
}

App::App(QString appId, QString userId, QString appName, QString appLasttime, QString appVer, qint32 cmtNum)
{
    this->appId = appId;
    this->userId = userId;
    this->appName = appName;
    this->appLasttime = appLasttime;
    this->appVer = appVer;
    this->cmtNum = cmtNum;
}

QString App::getAppId()
{
    if(appId != NULL)
        return this->appId;
    return "";
}

QString App::getUserId()
{
    if(userId != NULL)
        return this->userId;
    return "";
}

QString App::getAppName()
{
    if(appName != NULL)
        return this->appName;
    return "";
}

QString App::getAppLasttime()
{
    if(appLasttime != NULL)
        return this->appLasttime;
    return "";
}

QString App::getAppVer()
{
    if(appVer != NULL)
        return this->appVer;
    return "";
}

qint32 App::getCMTNum()
{
    if(cmtNum != NULL)
        return this->cmtNum;
    return 0;
}

void App::setAppId(QString appId)
{
    this->appId = appId;
}

void App::setUserId(QString userId)
{
    this->userId = userId;
}

void App::setAppName(QString appName)
{
    this->appName = appName;
}

void App::setAppLasttime(QString appLasttime)
{
    this->appLasttime = appLasttime;
}

void App::setAppVer(QString appVer)
{
    this->appVer = appVer;
}

void App::setCMTNum(qint32 cmtNum)
{
    this->cmtNum = cmtNum;
}
