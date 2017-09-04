#include "mainwindow.h"
#include "dataaccess.h"
#include <QApplication>

static const QString styleSheet =
        "QMainWindow { "
        "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #C0C0C0, stop: 0.8 #FFFFFF); "
        "}"

        "QTabWidget::pane { "
        "  border: 2px solid #BB7365; "
        "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #DEADA1, stop: 1 #FFFFFF); "
        "  border-radius: 4px; "
        "  margin-left: 8px; "
        "  margin-right: 8px; "
        "  margin-bottom: 8px; "
        "}"

        "QTabWidget::tab-bar { "
        "  alignment: center; "
        "}"

        "QTabBar::tab { "
        "  border: 2px solid #8F8F91; "
        "  border-bottom: 0px; "
        "  border-top-left-radius: 4px; "
        "  border-top-right-radius: 4px; "
        "  min-width: 20ex; "
        "  padding: 6px; "
        "}"

        "QTabBar::tab:selected { "
        "  border-color: #BB7365; "
        "  background: #DEADA1; "
        "  margin-left: -4px; "
        "  margin-right: -4px; "
        "}"

        "QTabBar::tab:!selected { "
        "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #F6F7FA, stop: 1 #DADBDE); "
        "  margin-top: 2px; "
        "}"

        "QTabBar::tab:first:selected { "
        "  margin-left: 0; "
        "}"

        "QTabBar::tab:last:selected { "
        "  margin-right: 0; "
        "}"

        "QTabBar::tab:only-one { "
        "  margin: 0; "
        "}"

        "QGroupBox { "
        "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #B3B3D7, stop: 1 #FFFFFF); "
        "  border: 2px solid #6B78B4; "
        "  border-radius: 5px; "
        "}"

        "QLineEdit, QListWidget, QListView { "
        "  min-height: 20px; "
        "  border: 1px solid #6B78B4; "
        "  border-radius: 4px; "
        "}"

        "QPushButton { "
        "  border: 2px solid #8F8F91; "
        "  border-radius: 6px; "
        "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #F6F7FA, stop: 1 #DADBDE); "
        "  min-width: 80px;"
        "  min-height: 22px;"
        "}";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(styleSheet);

    DataAccess dal;
    dal.OpenOrCreate();

    MainWindow w(dal);
    w.show();

    return a.exec();
}
