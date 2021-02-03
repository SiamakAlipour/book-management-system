#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>
#include <QListWidgetItem>
namespace Ui {
class UserPanel;
}

class UserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = nullptr);
    ~UserPanel();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_searchUserBook_clicked();

//    void on_listWidget_userBooks_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_userBooks_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_SignOut_clicked();

private:
    Ui::UserPanel *ui;
    void loadBooks();
    void searchBook(QString);
};

#endif // USERPANEL_H
