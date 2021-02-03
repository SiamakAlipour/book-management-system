#include "user.h"

User::User()
{

}

void User::setUserName(QString username)
{
    this->username = username;
}

QString User::getUserName()
{
    return this->username;
}

void User::setPassWord(QString password)
{
    this->password = password;
}

QString User::getPassWord()
{
    return this->password;
}

