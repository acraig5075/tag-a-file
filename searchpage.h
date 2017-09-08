#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

class DataAccess;
class QSqlQueryModel;


namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(DataAccess &dal, QWidget *parent = 0);
    ~SearchPage();

    void searchTag(const QString &tag);

public slots:
    void updateResultView();
    void setActive();

private slots:
    void onClipboardMenu();
    void onSearchMenu();

signals:
    void searchFile(int);

private:
    QString getSelectedFilename();

private:
    Ui::SearchPage *ui;
    DataAccess &m_dal;
    QSqlQueryModel *m_resultsModel = nullptr;
    QSqlQueryModel *m_tagsModel = nullptr;
};

#endif // SEARCHPAGE_H
