#include "comment.h"

Comment::Comment()
{
}

Comment::Comment(QString cmtId, QString appId, QString cmtTheme, QString cmtContent, qint32 creddit, bool cmtStates)
{
    this->cmt_id = cmtId;
    this->app_id = appId;
    this->cmt_theme = cmtTheme;
    this->cmt_content = cmtContent;
    this->creddit = creddit;
    this->cmt_states = cmtStates;
}

QString Comment::getCmtID()
{
    return cmt_id;
}

QString Comment::getAppId()
{
    return app_id;
}

QString Comment::getCmtTheme()
{
    return cmt_theme;
}

QString Comment::getCmtContent()
{
    return cmt_content;
}

qint32 Comment::getCmtCreddit()
{
    return creddit;
}

QString Comment::getCmtTime()
{
    return cmt_time;
}

bool Comment::getCmtStates()
{
    return cmt_states;
}

void Comment::setCmtID(QString cmtId)
{
    this->cmt_id = cmtId;
}

void Comment::setAppId(QString appId)
{
    this->app_id = appId;
}

void Comment::setCmtTheme(QString cmtTheme)
{
    this->cmt_theme = cmtTheme;
}

void Comment::setCmtContent(QString cmtContent)
{
    this->cmt_content = cmtContent;
}

void Comment::setCmtCreddit(qint32 creddit)
{
    this->creddit = creddit;
}

void Comment::setCmtTime(QString cmtTime)
{
    this->cmt_time = cmtTime;
}

void Comment::setCmtStates(bool cmtStates)
{
    this->cmt_states = cmtStates;
}
