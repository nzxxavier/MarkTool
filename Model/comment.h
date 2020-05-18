#ifndef COMMENT_H
#define COMMENT_H
#include <QString>

class Comment
{
public:
    Comment();
    Comment(QString cmtId, QString appId, QString cmtTheme, QString cmtContent, qint32 creddit, bool cmtStates);

    QString getCmtID();
    QString getAppId();
    QString getCmtTheme();
    QString getCmtContent();
    qint32 getCmtCreddit();
    QString getCmtTime();
    bool getCmtStates();

    void setCmtID(QString cmtId);
    void setAppId(QString appId);
    void setCmtTheme(QString cmtTheme);
    void setCmtContent(QString cmtContent);
    void setCmtCreddit(qint32 creddit);
    void setCmtTime(QString cmtTime);
    void setCmtStates(bool cmtStates);

    enum queryType
    {
        CMT_ID,
        APP_ID,
        ALL
    };

private:
    QString cmt_id;
    QString app_id;
    QString cmt_content;
    QString cmt_theme;
    qint32 creddit;
    QString cmt_time;
    bool cmt_states;
};

#endif // COMMENT_H
