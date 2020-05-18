#ifndef MARK_H
#define MARK_H
#include <QString>


class Mark
{
public:
    Mark();
    Mark(QString markId, QString userId, QString commentId, qint32 markClass, QString addTime = "", QString changeTime = "", qint32 markCredit = 0, QString markContent = "", QString markNote = "");

    QString getMarkId();
    QString getUserId();
    QString getCommentId();
    qint32 getMarkClass();
    QString getAddTime();
    QString getChangeTime();
    qint32 getMarkCredit();
    QString getMarkContent();
    QString getMarkNode();

    void setMarkId(QString markId);
    void setUserId(QString userId);
    void setCommentId(QString commentId);
    void setMarkClass(qint32 markClass);
    void setAddTime(QString addTime);
    void setChangeTime(QString changeTime);
    void setMarkCredit(qint32 markCredit);
    void setMarkContent(QString markContent);
    void setMarkNode(QString markNote);

    enum queryType
    {
        MARK_ID,
        USER_ID,
        COMMENT_ID,
        ALL
    };


    enum markClass{
        FEATURE = 1,
        NONFEATURE = 2,
        PERFORMANCE = 3,
        COMPATIBILITY = 4,
        USABILITY = 5,
        RELIABILITY = 6,
        SAFETY = 7,
        MAINTAINABILITY = 8,
        PORTABILITY = 9,
        OTHER = 10
    };

private:
    QString markId;
    QString userId;
    QString commentId;
    qint32 markClass;
    QString addTime;
    QString changeTime;
    qint32 markCredit;
    QString markContent;
    QString markNote;
};

#endif // MARK_H
