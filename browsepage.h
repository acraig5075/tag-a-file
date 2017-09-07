#ifndef BROWSEPAGE_H
#define BROWSEPAGE_H

#include <QWidget>

class DataAccess;
class QSqlQueryModel;

namespace Ui {
class BrowsePage;
}

class BrowsePage : public QWidget
{
    Q_OBJECT

public:
    explicit BrowsePage(DataAccess &dal, QWidget *parent = 0);
    ~BrowsePage();

private slots:
    void on_filesButton_clicked();
    void on_tagsButton_clicked();
    void onSearchMenu();
    void onEditMenu();
    void onDeleteMenu();

private:
    int getSelectedID();
    void refreshTableView();
    bool ValidateNewItemContent(QString &content);
    bool ValidateNewTagTitle(QString &title);

signals:
    void searchTag(int);
    void searchFile(int);

private:
    Ui::BrowsePage *ui;
    DataAccess &m_dal;
    QSqlQueryModel *m_filesModel = nullptr;
    QSqlQueryModel *m_tagsModel = nullptr;
};

#endif // BROWSEPAGE_H
