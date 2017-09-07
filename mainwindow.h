#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class EditPage;
class SearchPage;
class BrowsePage;
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

    void writePositionSettings();
    void readPositionSettings();
    void closeEvent( QCloseEvent* );

private slots:
    void tabChanged(int index);
    void onSearchFile(int id);
    void onSearchTag(int id);

private:
    Ui::MainWindow *ui;
    DataAccess &m_dal;
    EditPage *m_editPage = nullptr;
    SearchPage *m_searchPage = nullptr;
    BrowsePage *m_browsePage = nullptr;
};

#endif // MAINWINDOW_H
