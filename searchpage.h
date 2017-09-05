#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

class DataAccess;
class QStringListModel;


namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(DataAccess &dal, QWidget *parent = 0);
    ~SearchPage();

public slots:
    void updateResultView();
    void copyToClipboard();
    void setActive();

private:
    Ui::SearchPage *ui;
    DataAccess &m_dal;
    QStringListModel *m_model = nullptr;
};

#endif // SEARCHPAGE_H
