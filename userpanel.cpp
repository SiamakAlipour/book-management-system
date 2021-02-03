#include "userpanel.h"
#include "ui_userpanel.h"
#include "book.h"
#include "login.h"
#include "log.h"
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "QListWidget"

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    loadBooks();
    this->setWindowTitle("User Panel");
}

UserPanel::~UserPanel()
{
    delete ui;
}
void UserPanel::loadBooks(){
    QStringList items;

    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_userBooks;

    listWidget->clear();
//    item->setFlags(item->flags() | Qt::ItemIsEditable);
//    item->setCheckState(Qt::Unchecked);
    QFile inputFile("books.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       while (!in.atEnd())
       {

            QString line = in.readLine();
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(line);
            listWidget->addItem(item);

       }
    inputFile.close();
    }

}

void UserPanel::on_pushButton_2_clicked()
{
    loadBooks();
    Log x("User load books");
}

void UserPanel::on_pushButton_searchUserBook_clicked()
{
    QString bookname = ui->lineEdit_bookSearch->text();
    searchBook(bookname);

}
void UserPanel::searchBook(QString bookName){
    QString author_Name;
    QFile file("books.txt");
    if (!file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QMessageBox::information(0,"Error" , file.errorString());
    }
    QTextStream in(&file);

    while (!in.atEnd())
    {

         QString line = in.readLine();
         QStringList field = line.split(",");
         if ( field[0] == bookName ){
             QString Info = "Book Name : " + field[0] + "\n"
                     "Author Name : " + field[1];
             QMessageBox::about(this,"Book Information",Info);
             return;
         }
    }
    QMessageBox::information(this,"Error","Book not found");
    Log x("user searched book");
}


void UserPanel::on_listWidget_userBooks_itemDoubleClicked(QListWidgetItem *item)
{

    QStringList field = item->text().split(",");
    QString Info = "Book Name : " + field[0] + "\n"
            "Author Name : " + field[1];
    QMessageBox::about(this,"Book Information",Info);
}

void UserPanel::on_pushButton_SignOut_clicked()
{
    Login *loginWindow = new Login;
    loginWindow->show();
    this->close();
    Log x("User logged out");
}
