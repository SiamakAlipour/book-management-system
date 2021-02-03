#include "log.h"

Log::Log(QString jLog)
{
    QDate date = QDate::currentDate();
    QString date_text = date.toString();
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");

    QFile file("log.txt");
    if(!file.open(QIODevice::Append| QIODevice::Text)){
        QMessageBox::information(0,"Error",file.errorString());
    }
    QTextStream stream(&file);
    stream << jLog << " date : " << date_text <<" , time : " << time_text << "\n";

}
