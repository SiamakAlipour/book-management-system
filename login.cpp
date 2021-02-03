#include "login.h"
#include "adminpanel.h"
#include "userpanel.h"
#include "ui_login.h"
#include "QMessageBox"
#include "usermanage.h"
#include "user.h"
#include "log.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login Panel");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_adminButton_clicked()
{
    User admin;
    UserManage admins;
    admin.setUserName(ui->lineEdit_adminUser->text());
    admin.setPassWord(ui->lineEdit_adminPass->text());

    if (checkUser(admin.getUserName(),admin.getPassWord(),"admins.txt")){
        QMessageBox::information(0,"Login Sucess","Well done!");
        AdminPanel *window = new AdminPanel;
        window->show();
        this->close();
        Log x("admin logged in");


    }else{
        QMessageBox::information(this,"Admin Error","Wrong information");

    }

}

void Login::on_pushButton_userButton_clicked()
{
    User user;
    UserManage users;
    user.setUserName( ui->lineEdit_user->text());
    user.setPassWord ( ui->lineEdit_userPass->text());
    if (checkUser(user.getUserName() , user.getPassWord() , "users.txt")){
        QMessageBox::information(this,"User Login","Login Sucessfully");
        UserPanel *window = new UserPanel;
        window->show();
        this->close();

    }else{
        QMessageBox::information(this,"User Error","Wrong information");
    }
    Log x("user logged in");


}

bool Login::checkUser(QString username ,QString password,QString fileType)
{
    QFile file(fileType);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (username == fields[0] && password == fields[1]){
            return true;

        }else{
            continue;
        }
    }

    file.close();
    return false;

}
