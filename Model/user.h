#ifndef USER_H
#define USER_H
#include <QString>


class User
{
public:
    User();
    User(QString userId = "", QString userName = "", QString userPassword = "", QString userType = "normal");
    QString getUserId();
    QString getUserName();
    QString getUserPassword();
    QString getUserType();

    void setUserId(QString userId);
    void setUserName(QString userName);
    void setUserPassword(QString userPassword);
    void setUserType(QString userType);

    enum queryType
    {
        USER_ID,
        USER_NAME,
        ALL
    };
private:
    QString user_id;
    QString user_name;
    QString user_password;
    QString user_type;
};

#endif // USER_H
