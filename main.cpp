#include "mainwindow.h"
#include "dataaccess.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataAccess dal;
    dal.OpenOrCreate();

    MainWindow w(dal);
    w.show();

    return a.exec();
}
