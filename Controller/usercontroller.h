#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QDebug>
#include "Model/user.h"
#include "Model/comment.h"


class UserController
{
public:
    //构造单例模式（懒汉单例模式）
    ~UserController()
    {
        qDebug()<<"destructor called!";
    }

    UserController(const UserController&)=delete;
    UserController& operator=(const UserController&)=delete;

    static UserController& getInstance(){
        static UserController instance;
        return instance;
    }

    void changeUser(User* user){
        this->formalUser = user;
        loginState = true;
    }

    User* getFormalUser(){
        return formalUser;
    }

    bool isLogin(){
        return loginState;
    }

    void setCommentPool(QList<Comment*> list)
    {
        this->commentPool = list;
    }

    QList<Comment*> getCommentPool()
    {
        return commentPool;
    }

    void setCommentCount(qint32 count)
    {
        this->commentCount = count;
    }

    qint32 getCommentCount()
    {
        return commentCount;
    }

    enum TYPE{
        normal,
        admin
    };

private:
    UserController(){
        qDebug()<<"constructor called!";
    }

    User* formalUser;
    bool loginState = false;
    QList<Comment*> commentPool;
    qint32 commentCount = 0;
};

#endif // USERCONTROLLER_H
