#include "bookmanage.h"

BookManage::BookManage()
{

}

void BookManage::setBook(QString bookName, QString authorName, QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream stream(&file);
    stream << bookName << "," << authorName << "\n";

    file.close();
}
