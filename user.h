#ifndef USER_H
#define USER_H

#include <QWidget>

class User
{
private:
    QString username;
    QString password;
public:
    User();
    void setUserName(QString);
    QString getUserName(void);

    void setPassWord(QString);
    QString getPassWord(void);

};

#endif // USER_H
