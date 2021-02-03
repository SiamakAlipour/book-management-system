#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "login.h"
#include "user.h"

class UserManage
{
public:
    UserManage();
    void setUser(QString , QString , QString);

};

#endif // USERMANAGE_H
