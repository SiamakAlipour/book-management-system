#include "usermanager.h"
#include <QFile>
bool lessThan(User* u1, User* u2){
    return u1->id() < u2->id();
}

UserManager::UserManager()
{
    m_lastId = 0;
}

bool UserManager::readUsers(const QString &fileName)
{
    QFile file(fileName);
    if (!file.exists()){
        qDebug() << QString("Error: File not found: '%1'").arg(fileName);
        return false;
    }

    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        stream.readLine(); // drop header
        while (!stream.atEnd()){
            QString data = stream.readLine();
            User *user = new User();
            user->setData(data);
            m_lastId = (user->id() > m_lastId) ? user->id() : m_lastId;
            m_users.insert(user->username(), user);
        }
        return true;
    } else {
        qDebug() << QString("Error: Could not open file '%1'").arg(fileName);
    }
    return false;
}


bool UserManager::writeUsers(const QString &fileName)
{
    QFile file(fileName);
    QList<User*> list = m_users.values();
    qSort(list.begin(), list.end(), lessThan);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        foreach(User *user, list){
            stream << *user;
        }
        return true;
    } else {
        qDebug() << QString("Error: Could not open file '%1'").arg(fileName);
    }
    return false;
}


bool UserManager::userExists(const QString &username) const
{
    return m_users.keys().contains(username);
}


bool UserManager::addUser(const QString &userName, const QString &name, const QString &password)
{
    if (m_users.contains(userName)){
        qDebug() << QString("User '%1' already exists").arg(userName);
        return false;
    }

    User *user = new User;
    user->setId(++m_lastId);
    user->setUserName(userName);
    user->setName(name);
    user->setPassword(password);
    m_users.insert(userName, user);
    return true;
}


bool UserManager::checkPassword(QString username, QString password) const
{
    if (m_users.keys().contains(username)){
        return m_users.value(username)->password() == password;
    }
    return false;
}

int UserManager::lastId() const
{
    return m_lastId;
}
