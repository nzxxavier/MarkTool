#ifndef CORRECTION_H
#define CORRECTION_H
#include <QString>

class Correction
{
public:
    Correction();
    Correction(QString correctID, QString markId, QString correctTime, qint32 markClass, qint32 markCreddit, QString markContent);

    QString getCorrectID();
    QString getMarkId();
    QString getCorrectTime();
    qint32 getMarkClass();
    qint32 getMarkCreddit();
    QString getMarkContent();

    void setCorrectID(QString correctID);
    void setMarkId(QString markId);
    void setCorrectTime(QString correctTime);
    void setMarkClass(qint32 markClass);
    void setMarkCreddit(qint32 markCreddit);
    void setMarkContent(QString markContent);

    enum queryType
    {
        CORRECT_ID,
        MARK_ID,
        ALL
    };

private:
    QString correct_id;
    QString mark_id;
    QString correct_time;
    qint32 mark_class;
    qint32 mark_creddit;
    QString mark_content;
};

#endif // CORRECTION_H
