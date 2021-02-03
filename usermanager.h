#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QWidget>
#include "user.h"

class UserManager
{
public:
    UserManager();

    bool readUsers(const QString &fileName);
    bool writeUsers(const QString &fileName);

    bool userExists(const QString &username) const;
    bool addUser(const QString &username, const QString &name, const QString &password);
    bool checkPassword(QString username, QString password) const;
    int lastId() const;

private:
    QMap<QString, User*> m_users;
    int m_lastId;
};

#endif // USERMANAGER_H
