#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class EditPage;
class SearchPage;
class DataAccess;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DataAccess &dal, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DataAccess &m_dal;
    EditPage *m_editPage = nullptr;
    SearchPage *m_searchPage = nullptr;

};

#endif // MAINWINDOW_H
