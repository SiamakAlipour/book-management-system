#include "login.h"
#include "adminpanel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setWindowTitle("Login Page");
    w.show();
    return a.exec();
}
