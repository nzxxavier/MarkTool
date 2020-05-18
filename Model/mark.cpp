#include "mark.h"

Mark::Mark()
{
}

Mark::Mark(QString markId, QString userId, QString commentId, qint32 markClass, QString addTime, QString changeTime, qint32 markCredit, QString markContent, QString markNote)
{
    this->markId = markId;
    this->userId = userId;
    this->commentId = commentId;
    this->markClass = markClass;
    this->addTime = addTime;
    this->changeTime = changeTime;
    this->markCredit = markCredit;
    this->markContent = markContent;
    this->markNote = markNote;
}

QString Mark::getMarkId()
{
    return this->markId;
}

QString Mark::getUserId()
{
    return this->userId;
}

QString Mark::getCommentId()
{
    return this->commentId;
}

qint32 Mark::getMarkClass()
{
    return this->markClass;
}

QString Mark::getAddTime()
{
    return this->addTime;
}

QString Mark::getChangeTime()
{
    return this->changeTime;
}

qint32 Mark::getMarkCredit()
{
    return this->markCredit;
}

QString Mark::getMarkContent()
{
    return this->markContent;
}

QString Mark::getMarkNode()
{
    return this->markNote;
}

void Mark::setMarkId(QString markId)
{
    this->markId = markId;
}

void Mark::setUserId(QString userId)
{
    this->userId = userId;
}

void Mark::setCommentId(QString commentId)
{
    this->commentId = commentId;
}

void Mark::setMarkClass(qint32 markClass)
{
    this->markClass = markClass;
}

void Mark::setAddTime(QString addTime)
{
    this->addTime = addTime;
}

void Mark::setChangeTime(QString changeTime)
{
    this->changeTime = changeTime;
}

void Mark::setMarkCredit(qint32 markCredit)
{
    this->markCredit = markCredit;
}

void Mark::setMarkContent(QString markContent)
{
    this->markContent = markContent;
}

void Mark::setMarkNode(QString markNote)
{
    this->markNote = markNote;
}
