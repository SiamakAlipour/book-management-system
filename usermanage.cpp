#include "usermanage.h"

UserManage::UserManage()
{

}

void UserManage::setUser(QString username, QString password , QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream stream(&file);
    stream << username << "," << password << "\n";

    file.close();
}


