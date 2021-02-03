#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include "user.h"
#include <QListWidgetItem>
namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    void delay();
    void loadBooks();
    void loadUsers();
    void submitEdit(QString,QListWidget*);
    void searchBook(QString);
    bool userExistCheck (QListWidget* , User);
    ~AdminPanel();

private slots:
    void on_pushButton_addBook_clicked();

    void on_listWidget_books_itemClicked(QListWidgetItem *item);

    void on_pushButton_addUser_clicked();



    void on_pushButton_refreshBookList_clicked();

    void on_pushButton_submitEdit_clicked();

    void on_pushButton_SignOut_clicked();

    void on_pushButton_refreshUserList_clicked();

    void on_pushButton_submitUserEdit_clicked();

    void on_listWidget_users_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_H
