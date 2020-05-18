#include "user.h"

User::User()
{

}

User::User(QString userId, QString userName, QString userPassword, QString userType)
{
    this->user_id = userId;
    this->user_name = userName;
    this->user_password = userPassword;
    this->user_type = userType;
}

 QString User::getUserId()
{
    return this->user_id;
}

 QString User::getUserName()
{
    return this->user_name;
}

 QString User::getUserPassword()
{
    return this->user_password;
}

 QString User::getUserType(){
    return this->user_type;
}

void User::setUserId( QString userId)
{
    this->user_id = userId;
}

void User::setUserName( QString userName)
{
    this->user_name = userName;
}

void User::setUserPassword( QString userPassword)
{
    this->user_password = userPassword;
}

void User::setUserType( QString userType)
{
    this->user_type = userType;
}
