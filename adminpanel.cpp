#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "user.h"
#include "usermanage.h"
#include "book.h"
#include "bookmanage.h"
#include "log.h"
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QDir>




AdminPanel::AdminPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    loadBooks();
    loadUsers();
    this->setWindowTitle("Admin Panel");

}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_pushButton_addBook_clicked()
{
    Book book;
    BookManage bookManage;
    book.setBookName( ui->lineEdit_bookName->text());
    book.setBookAuthor(ui->lineEdit_authorName->text());
    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_books;

    QListWidgetItem *item = new QListWidgetItem;
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    QFile file("books.txt");

    if(file.open(QIODevice::Append|QIODevice::Text)){
        for(int i = 0; i < listWidget->count(); i++)
        {
            if(listWidget->item(i)->text().split(",")[0].toLower() == book.getBookName().toLower()){
                QMessageBox::information(this,"Error" , "کتاب موجود است");
                return;
            }
        }
        QTextStream stream(&file);
        if(book.getBookName() != ""){
            QStringList strList;
            strList << book.getBookName() << book.getBookAuthor();
            item->setText(strList.join(","));
            item->setCheckState(Qt::Unchecked);
            listWidget->addItem(item);
            bookManage.setBook(book.getBookName(),book.getBookAuthor(),"books.txt");
        }else{
            QMessageBox::information(this,"error","book name is empty");
        }

    }
    file.close();
    ui->lineEdit_bookName->text()="";
    ui->lineEdit_authorName->text()="";
    Log x("book added Admin");
}

void AdminPanel::on_listWidget_books_itemClicked(QListWidgetItem *item)
{
    QListWidget *listWidget = new QListWidget;

    QStringList lineLists;
    listWidget = ui->listWidget_books;

    if(item->checkState() == Qt::Checked){
        delay();
        listWidget->takeItem(listWidget->row(item));
        submitEdit("books.txt",listWidget);
        Log x("book removed Admin");
    }



}
void AdminPanel::delay(){
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



void AdminPanel::on_pushButton_addUser_clicked()
{
    User user;
    UserManage users;
    UserManage admins;

    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_users;

    QListWidgetItem *item = new QListWidgetItem;
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    user.setUserName( ui->lineEdit_addUser->text() );
    user.setPassWord(  ui->lineEdit_addPass->text() );
    if(user.getUserName() != "" && user.getPassWord() != ""){
        if(ui->comboBox_addUser->currentText() == "admin"){

            admins.setUser(user.getUserName() , user.getPassWord() , "admins.txt");
        }
        else if(ui->comboBox_addUser->currentText() == "user"){
            if(userExistCheck(ui->listWidget_users,user)){
                QMessageBox::information(this,"Error" , "User exist");
                return;
            }
            QStringList strList;
            strList << user.getUserName() << user.getPassWord();
            item->setText(strList.join(","));
            item->setCheckState(Qt::Unchecked);
            listWidget->addItem(item);
            users.setUser(user.getUserName() , user.getPassWord() , "users.txt");
        }
    }
    else{
        QMessageBox::information(this,"error","username or password is empty");
    }
    Log x("User added");
}

void AdminPanel::loadBooks(){
    QStringList items;

    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_books;
    listWidget->clear();

    QFile inputFile("books.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       while (!in.atEnd())
       {

            QString line = in.readLine();
            QListWidgetItem *item = new QListWidgetItem;
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            item->setCheckState(Qt::Unchecked);
            item->setText(line);
            listWidget->addItem(item);

       }
    inputFile.close();
    }
}
void AdminPanel::loadUsers(){
    QStringList items;

    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_users;
    listWidget->clear();

    QFile inputFile("users.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       while (!in.atEnd())
       {

            QString line = in.readLine();
            QListWidgetItem *item = new QListWidgetItem;
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            item->setCheckState(Qt::Unchecked);
            item->setText(line);
            listWidget->addItem(item);

       }
    inputFile.close();
    }

}

void AdminPanel::on_pushButton_refreshBookList_clicked()
{
    loadBooks();
    Log x("books list refreshed");
}

void AdminPanel::on_pushButton_submitEdit_clicked()
{
    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_books;

    QListWidgetItem *item = new QListWidgetItem;
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    QFile file("books.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0,"Error" , "File not opened");
    }
    QTextStream stream(&file);
    for (int i = 0 ; i < listWidget->count() ; i++){
        QListWidgetItem* item = listWidget->item(i);
        stream<<item->text() << "\n";
    }
    file.close();
    Log x("books list been editted");
}

void AdminPanel::on_pushButton_SignOut_clicked()
{
    Login *loginWindow = new Login;
    loginWindow->show();
    this->close();
    Log x("Admin Signed Out");
}

void AdminPanel::on_pushButton_refreshUserList_clicked()
{
    loadUsers();
    Log x("userlist refreshed");
}

void AdminPanel::on_pushButton_submitUserEdit_clicked()
{
    QListWidget *listWidget = new QListWidget;
    listWidget = ui->listWidget_users;

    QListWidgetItem *item = new QListWidgetItem;
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    QFile file("users.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0,"Error" , "File not opened");
    }
    QTextStream stream(&file);
    for (int i = 0 ; i < listWidget->count() ; i++){
        QListWidgetItem* item = listWidget->item(i);
        stream<<item->text() << "\n";
    }
    file.close();
    Log x("user list editted");
}

void AdminPanel::on_listWidget_users_itemClicked(QListWidgetItem *item)
{
    QListWidget *listWidget = new QListWidget;

    QStringList lineLists;
    listWidget = ui->listWidget_users;

    if(item->checkState() == Qt::Checked){
        delay();
        listWidget->takeItem(listWidget->row(item));
        submitEdit("users.txt",listWidget);
    }
    Log x("user been removed");
}

void AdminPanel::submitEdit(QString filePath , QListWidget *listWidget){
//    QListWidget *listWidget = new QListWidget;
//    listWidget = ui->listWidget_users;

    QListWidgetItem *item = new QListWidgetItem;
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0,"Error" , "File not opened");
    }
    QTextStream stream(&file);
    for (int i = 0 ; i < listWidget->count() ; i++){
        QListWidgetItem* item = listWidget->item(i);
        stream<<item->text() << "\n";
    }
    file.close();
}
bool AdminPanel::userExistCheck(QListWidget* listWidget,User user){
    for(int i = 0; i < listWidget->count(); i++)
    {
        if(listWidget->item(i)->text().split(",")[0].toLower() == user.getUserName().toLower()){
            return true;
        }
    }
    return false;
}

void AdminPanel::on_pushButton_clicked()
{
    QString bookname = ui->lineEdit_bookName->text();
    searchBook(bookname);
}
void AdminPanel::searchBook(QString bookName){
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

