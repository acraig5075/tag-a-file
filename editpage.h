#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>

class DataAccess;
class QSqlQueryModel;
class QCompleter;


namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    explicit EditPage(DataAccess &dal, QWidget *parent = 0);
    ~EditPage();

    void setActive();
    void editContent(const QString &content);

private slots:
    void on_browseButton_clicked();
    void on_pushButton_clicked();

    void resetTagList();

private:
    Ui::EditPage *ui;
    DataAccess &m_dal;
    QSqlQueryModel *m_tagModel = nullptr;
};

#endif // EDITPAGE_H
