#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool checkUser(QString,QString,QString);

private slots:
    void on_pushButton_adminButton_clicked();

    void on_pushButton_userButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
