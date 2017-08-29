#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

class DataAccess;

namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(DataAccess &dal, QWidget *parent = 0);
    ~SearchPage();

private:
    void updateResultView();

private slots:
    void on_tagEdit_returnPressed();

private:
    Ui::SearchPage *ui;
    DataAccess &m_dal;
};

#endif // SEARCHPAGE_H
