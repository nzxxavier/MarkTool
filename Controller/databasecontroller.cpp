#include "databasecontroller.h"

bool DataBaseController::initConnection(QString url, QString name, QString password, QString Database)
{
    if(!db.isOpen())
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(url);
        db.setUserName(name);
        db.setPassword(password);
        db.setDatabaseName(Database);

        return db.open();
    }
    else
        return true;
}

QString DataBaseController::lastError()
{
    return this->error;
}

bool DataBaseController::insertUser(QString username, QString password)
{
    QString insertString = "INSERT INTO `marktool`.`user`\
            (`user_id`,\
            `user_name`,\
            `user_password`,\
            `user_avatar`,\
            `user_type`)\
            VALUES\
            (\"" + genUUID() + "\",\
            \"" + username + "\",\
            \"" + password + "\",\
            \"\",\
            \"normal\");";
    return execSQL(insertString);
}

bool DataBaseController::insertApp(QString userId, QString appName, QString appVer)
{
    QString insertString = "INSERT INTO `marktool`.`app`\
            (`app_id`,\
            `user_id`,\
            `app_name`,\
            `app_lasttime`,\
            `app_ver`,\
            `comment_num`)\
            VALUES\
            (\"" + genUUID() + "\",\
            \"" + userId + "\",\
            \"" + appName + "\",\
            \"" + genTime() + "\",\
            \"" + appVer + "\",\
            0);";
    return execSQL(insertString);
}

bool DataBaseController::insertOldApp(QString appId, QString userId, QString appName, QString appVer)
{
    QString insertString = "INSERT INTO `marktool`.`app`\
            (`app_id`,\
            `user_id`,\
            `app_name`,\
            `app_lasttime`,\
            `app_ver`,\
            `comment_num`)\
            VALUES\
            (\"" + appId + "\",\
            \"" + userId + "\",\
            \"" + appName + "\",\
            \"" + genTime() + "\",\
            \"" + appVer + "\",\
            0);";
    return execSQL(insertString);
}

QString DataBaseController::insertComment(QString appName, QString commentTheme, QString commentContent, qint32 commentCreddit)
{
    QString uuid = genUUID();
    App* app = this->queryApp(appName, App::APP_NAME).at(0);
    QString insertString = QString("INSERT INTO `marktool`.`comment`"
                                   "(`cmt_id`,"
                                   "`app_id`,"
                                   "`cmt_theme`,"
                                   "`cmt_content`,"
                                   "`cmt_creddit`,"
                                   "`cmt_time`,"
                                   "`cmt_states`)"
                                   "VALUES"
                                   "(\"" + uuid + "\","
                                   "\"" + app->getAppId() + "\","
                                   "\"" + commentTheme + "\","
                                   "\"" + commentContent + "\","
                                   "" + QString::number(commentCreddit) + ","
                                   "\"" + genTime() + "\","
                                   "false);");
    if(execSQL(insertString))
        return uuid;
    else
        return "";
}

bool DataBaseController::insertOldComment(QString cmtId, QString appName, QString commentTheme, QString commentContent, qint32 commentCreddit)
{
    UserController& uc = UserController::getInstance();
    App* app;
    QList<App*> list = this->queryApp(appName, App::APP_NAME);
    if(list.size() < 1)
    {
        this->insertApp(uc.getFormalUser()->getUserId(), appName, "");
        app = this->queryApp(appName, App::APP_NAME).at(0);
    }
    else
    {
        app = list.at(0);
    }
    QString insertString = QString("INSERT INTO `marktool`.`comment`"
                                   "(`cmt_id`,"
                                   "`app_id`,"
                                   "`cmt_theme`,"
                                   "`cmt_content`,"
                                   "`cmt_creddit`,"
                                   "`cmt_time`,"
                                   "`cmt_states`)"
                                   "VALUES"
                                   "(\"" + cmtId + "\","
                                   "\"" + app->getAppId() + "\","
                                   "\"" + commentTheme + "\","
                                   "\"" + commentContent + "\","
                                   "" + QString::number(commentCreddit) + ","
                                   "\"" + genTime() + "\","
                                   "false);");
    return execSQL(insertString);
}

bool DataBaseController::insertMark(QString userId, QString commentId, qint32 markClass, qint32 markCreddit, QString markContent, QString markNote)
{
    QString insertString = QString("INSERT INTO `marktool`.`mark`"
                                   "(`mark_id`,"
                                   "`user_id`,"
                                   "`cmt_id`,"
                                   "`add_time`,"
                                   "`change_time`,"
                                   "`mark_class`,"
                                   "`mark_creddit`,"
                                   "`mark_content`,"
                                   "`mark_note`)"
                                   "VALUES"
                                   "(\"" + genUUID() + "\","
                                   "\"" + userId + "\","
                                   "\"" + commentId + "\","
                                   "\"" + genTime() + "\","
                                   "\"N/A\","
                                   "" + QString::number(markClass) + ","
                                   "" + QString::number(markCreddit) + ","
                                   "\"" + markContent + "\","
                                   "\"" + markNote + "\");");
    return execSQL(insertString);
}

bool DataBaseController::insertOldMark(QString markId, QString userId, QString commentId, qint32 markClass, qint32 markCreddit, QString markContent, QString markNote)
{
    QString insertString = QString("INSERT INTO `marktool`.`mark`"
                                   "(`mark_id`,"
                                   "`user_id`,"
                                   "`cmt_id`,"
                                   "`add_time`,"
                                   "`change_time`,"
                                   "`mark_class`,"
                                   "`mark_creddit`,"
                                   "`mark_content`,"
                                   "`mark_note`)"
                                   "VALUES"
                                   "(\"" + markId + "\","
                                   "\"" + userId + "\","
                                   "\"" + commentId + "\","
                                   "\"" + genTime() + "\","
                                   "\"N/A\","
                                   "" + QString::number(markClass) + ","
                                   "" + QString::number(markCreddit) + ","
                                   "\"" + markContent + "\","
                                   "\"" + markNote + "\");");
    return execSQL(insertString);
}

bool DataBaseController::insertCorrect(QString markId, qint32 markClass, qint32 markCreddit, QString markContent)
{
    QString insertString = QString("INSERT INTO `marktool`.`correction`"
                                   "(`correct_id`,"
                                   "`mark_id`,"
                                   "`correct_time`,"
                                   "`mark_class`,"
                                   "`mark_creddit`,"
                                   "`mark_content`,"
                                   "`correct_state`)"
                                   "VALUES"
                                   "(\"" + genUUID() + "\","
                                   "\"" + markId + "\","
                                   "\"" + genTime() + "\","
                                   "" + QString::number(markClass) + ","
                                   ""+ QString::number(markCreddit) +","
                                   "\"" + markContent + "\","
                                   "TRUE)");
    return execSQL(insertString);
}

bool DataBaseController::insertOldCorrect(QString correctionId, QString markId, qint32 markClass, qint32 markCreddit, QString markContent)
{
    QString insertString = QString("INSERT INTO `marktool`.`correction`"
                                   "(`correct_id`,"
                                   "`mark_id`,"
                                   "`correct_time`,"
                                   "`mark_class`,"
                                   "`mark_creddit`,"
                                   "`mark_content`,"
                                   "`correct_state`)"
                                   "VALUES"
                                   "(\"" + correctionId + "\","
                                   "\"" + markId + "\","
                                   "\"" + genTime() + "\","
                                   "" + QString::number(markClass) + ","
                                   ""+ QString::number(markCreddit) +","
                                   "\"" + markContent + "\","
                                   "TRUE)");
    return execSQL(insertString);
}

User* DataBaseController::queryUser(QString value, User::queryType type)
{
    QSqlQuery query;
    QString queryString;
    User* user = nullptr;

    if (type == User::USER_ID)
        queryString = "SELECT * FROM USER WHERE user_id = \"" + value + "\";";
    else
        queryString = "SELECT * FROM USER WHERE user_name = \"" + value + "\";";

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString userId = query.value("user_id").toString();
        QString userName = query.value("user_name").toString();
        QString userPassword = query.value("user_password").toString();
        QString userType = query.value("user_type").toString();

        user = new User(userId, userName, userPassword, userType);
    }

    return user;
}

QList<App*> DataBaseController::queryApp(QString value, App::queryType type)
{
    QSqlQuery query;
    QString queryString;
    QList<App*> apps;

    switch (type) {
        case App::USER_ID:
        queryString = "SELECT * FROM APP WHERE user_id = \"" + value + "\";";
        break;
    case App::APP_NAME:
        queryString = "SELECT * FROM APP WHERE app_name = \"" + value + "\";";
        break;
    case App::APP_ID:
        queryString = "SELECT * FROM APP WHERE app_id = \"" + value + "\";";
        break;
    case App::ALL:
        queryString = "SELECT * FROM APP";
    }

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString app_id = query.value("app_id").toString();
        QString user_id = query.value("user_id").toString();
        QString app_name = query.value("app_name").toString();
        QString app_lasttime = query.value("app_lasttime").toString();
        QString app_ver = query.value("app_ver").toString();
        qint32 comment_num = query.value("comment_num").toInt();
        App* app = new App(app_id, user_id, app_name, app_lasttime, app_ver, comment_num);

        apps.append(app);
    }

    return apps;
}

QList<Mark*> DataBaseController::queryMark(QString value, Mark::queryType type)
{
    QSqlQuery query;
    QString queryString;
    QList<Mark*> marks;

    switch (type) {
        case Mark::MARK_ID:
        queryString = "SELECT * FROM MARK WHERE mark_id = \"" + value + "\";";
        break;
        case Mark::USER_ID:
        queryString = "SELECT * FROM MARK WHERE user_id = \"" + value + "\";";
        break;
        case Mark::COMMENT_ID:
        queryString = "SELECT * FROM MARK WHERE cmt_id = \"" + value + "\";";
        break;
    case Mark::ALL:
        queryString = "SELECT * FROM MARK";
    }

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString mark_id = query.value("mark_id").toString();
        QString user_id = query.value("user_id").toString();
        QString cmt_id = query.value("cmt_id").toString();
        QString add_time = query.value("add_time").toString();
        QString change_time = query.value("change_time").toString();
        qint32 mark_class = query.value("mark_class").toInt();
        qint32 mark_creddit = query.value("mark_creddit").toInt();
        QString mark_content = query.value("mark_content").toString();
        QString mark_note = query.value("mark_note").toString();
        Mark* mark = new Mark(mark_id, user_id, cmt_id, mark_class, add_time, change_time, mark_creddit, mark_content, mark_note);

        marks.append(mark);
    }

    return marks;
}

QList<Mark*> DataBaseController::queryMarkWithoutCorrect()
{
    QSqlQuery query;
    QString queryString = "select * from mark left join correction on mark.mark_id where correction.mark_id is null;";
    QList<Mark*> marks;

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString mark_id = query.value("mark_id").toString();
        QString user_id = query.value("user_id").toString();
        QString cmt_id = query.value("cmt_id").toString();
        QString add_time = query.value("add_time").toString();
        QString change_time = query.value("change_time").toString();
        qint32 mark_class = query.value("mark_class").toInt();
        qint32 mark_creddit = query.value("mark_creddit").toInt();
        QString mark_content = query.value("mark_content").toString();
        QString mark_note = query.value("mark_note").toString();
        Mark* mark = new Mark(mark_id, user_id, cmt_id, mark_class, add_time, change_time, mark_creddit, mark_content, mark_note);

        marks.append(mark);
    }

    return marks;
}

bool DataBaseController::deleteApp(QString value, App::queryType type)
{
    QSqlQuery query;
    QString queryString;
    QList<App*> apps;

    switch (type) {
        case App::USER_ID:
            queryString = "DELETE FROM `app` WHERE user_id = \"" + value + "\";";
        break;
    case App::APP_NAME:
            queryString = "DELETE FROM `app` WHERE app_name = \"" + value + "\";";
        break;
    case App::APP_ID:
            queryString = "DELETE FROM `app` WHERE app_id = \"" + value + "\";";
    }

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
        return false;
    }
    return true;
}

QList<Comment*> DataBaseController::queryComment(QString value, Comment::queryType type)
{
    QSqlQuery query;
    QString queryString;
    QList<Comment*> comments;

    switch (type) {
        case Comment::APP_ID:
        queryString = "SELECT * FROM `comment` WHERE app_id = \"" + value + "\";";
        break;
        case Comment::CMT_ID:
        queryString = "SELECT * FROM `comment` WHERE cmt_id = \"" + value + "\";";
        break;
    case Comment::ALL:
        queryString = "SELECT * FROM `comment`";
    }

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString cmt_id = query.value("cmt_id").toString();
        QString app_id = query.value("app_id").toString();
        QString cmt_theme = query.value("cmt_theme").toString();
        QString cmt_content = query.value("cmt_content").toString();
        qint32 cmt_creddit = query.value("cmt_creddit").toInt();
        bool cmt_states = query.value("cmt_states").toBool();
        Comment* comment = new Comment(cmt_id, app_id, cmt_theme, cmt_content, cmt_creddit, cmt_states);
        comments.append(comment);
    }

    return comments;
}

QList<Correction*> DataBaseController::queryCorrection(QString value, Correction::queryType type)
{
    QSqlQuery query;
    QString queryString;
    QList<Correction*> corrects;

    switch (type) {
        case Correction::CORRECT_ID:
        queryString = "SELECT * FROM `correction` WHERE correct_id = \"" + value + "\";";
        break;
        case Correction::MARK_ID:
        queryString = "SELECT * FROM `correction` WHERE mark_id = \"" + value + "\";";
        break;
        case Correction::ALL:
        queryString = "SELECT * FROM `correction`";
    }

    query.exec(queryString);
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
    }

    while(query.next())
    {
        QString correct_id = query.value("correct_id").toString();
        QString mark_id = query.value("mark_id").toString();
        QString correct_time = query.value("correct_time").toString();
        qint32 mark_class = query.value("mark_class").toInt();
        qint32 mark_creddit = query.value("mark_creddit").toInt();
        QString mark_content = query.value("mark_content").toString();
        Correction* correst = new Correction(correct_id, mark_id, correct_time, mark_class, mark_creddit, mark_content);
        corrects.append(correst);
    }

    return corrects;
}

QString DataBaseController::genUUID()
{
    return UUIDController::getUUID().remove("-").remove("{").remove("}");
}

QString DataBaseController::genTime()
{
    QDateTime dateTime(QDateTime::currentDateTime());
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

bool DataBaseController::execSQL(QString sql)
{
    QSqlQuery query;
    db.transaction();
    query.exec(sql);
    db.commit();
    QSqlError error = query.lastError();
    if(error.isValid())
    {
        switch (error.type()) {
        case QSqlError::NoError:
            this->error = "无错误";
            break;
        case QSqlError::ConnectionError://连接错语
            this->error = error.text();
            break;
        case QSqlError::StatementError://语句错语
            this->error = error.text();
            break;
        case QSqlError::TransactionError://事务错误
            this->error = error.text();
            break;
        default://未知错误
            this->error = error.text();
            break;
        }
        return false;
    }
    return true;
}
