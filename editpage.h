#ifndef EDITPAGE_H
#define EDITPAGE_H

#include <QWidget>

class DataAccess;

namespace Ui {
class EditPage;
}

class EditPage : public QWidget
{
    Q_OBJECT

public:
    explicit EditPage(DataAccess &dal, QWidget *parent = 0);
    ~EditPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EditPage *ui;
    DataAccess &m_dal;
};

#endif // EDITPAGE_H
