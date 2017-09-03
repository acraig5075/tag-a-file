#ifndef TAGLINEEDIT_H
#define TAGLINEEDIT_H
#include <QLineEdit>

class QWidget;
class TagListWidget;

class TagLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    TagLineEdit(QWidget *parent);

    void setBuddyList(TagListWidget *buddyList);

private slots:
    void onTextEdited(const QString &arg1);
    void onReturnPressed();

private:
    TagListWidget *m_buddyList = nullptr;
};

#endif // TAGLINEEDIT_H
