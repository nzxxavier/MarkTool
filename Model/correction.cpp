#include "correction.h"

Correction::Correction(QString correctID, QString markId, QString correctTime, qint32 markClass, qint32 markCreddit, QString markContent)
{
    this->correct_id = correctID;
    this->mark_id = markId;
    this->correct_time = correctTime;
    this->mark_class = markClass;
    this->mark_creddit = markCreddit;
    this->mark_content = markContent;
}

QString Correction::getCorrectID()
{
    return this->correct_id;
}

QString Correction::getMarkId()
{
    return this->mark_id;
}

QString Correction::getCorrectTime()
{
    return this->correct_time;
}

qint32 Correction::getMarkClass()
{
    return this->mark_class;
}

qint32 Correction::getMarkCreddit()
{
    return this->mark_creddit;
}

QString Correction::getMarkContent()
{
    return this->mark_content;
}

void Correction::setCorrectID(QString correctID)
{
    this->correct_id = correctID;
}

void Correction::setMarkId(QString markId)
{
    this->mark_id = markId;
}

void Correction::setCorrectTime(QString correctTime)
{
    this->correct_time = correctTime;
}

void Correction::setMarkClass(qint32 markClass)
{
    this->mark_class = markClass;
}

void Correction::setMarkCreddit(qint32 markCreddit)
{
    this->mark_creddit = markCreddit;
}

void Correction::setMarkContent(QString markContent)
{
    this->mark_content = markContent;
}
