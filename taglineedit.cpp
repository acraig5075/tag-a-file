#include "taglineedit.h"
#include "taglistwidget.h"
#include <QRegExpValidator>


TagLineEdit::TagLineEdit(QWidget *parent)
  : QLineEdit(parent)
{
    setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9][a-zA-Z0-9 -]+$"), this));

    QObject::connect(this, SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    QObject::connect(this, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
}

void TagLineEdit::setBuddyList(TagListWidget *buddyList)
{
    m_buddyList = buddyList;
}

void TagLineEdit::onTextEdited(const QString &arg1)
{
    QString arg = arg1;
    arg = arg.replace(' ', '-');
    arg = arg.toLower();
    setText(arg);
}

void TagLineEdit::onReturnPressed()
{
    if (!m_buddyList)
        return;

    QString value = text();

    while (value.endsWith('-'))
        value.chop(1);
    while (value.contains("--"))
        value.replace("--", "-");

    if (!value.isEmpty())
    {
        auto matches = m_buddyList->findItems(value, Qt::MatchExactly);
        if (matches.isEmpty())
        {
            m_buddyList->addTagItem(value);
            clear();
            setFocus();
        }
    }
}
