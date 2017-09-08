#ifndef TAGLINEEDIT_H
#define TAGLINEEDIT_H
#include <QLineEdit>

class QWidget;
class TagListWidget;
class QSqlQueryModel;

class TagLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    TagLineEdit(QWidget *parent);

    void setBuddyList(TagListWidget *buddyList);
    void setTagCompleter(QSqlQueryModel &model);

private slots:
    void onTextEdited(const QString &arg1);
    void onReturnPressed();

private:
    QCompleter *m_completer = nullptr;
    TagListWidget *m_buddyList = nullptr;
};

#endif // TAGLINEEDIT_H
