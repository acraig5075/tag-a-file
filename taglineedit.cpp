#include "taglineedit.h"
#include <QRegExpValidator>

TagLineEdit::TagLineEdit(QWidget *parent)
  : QLineEdit(parent)
{
    setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9][a-zA-Z0-9 -]+$"), this));

    QObject::connect(this, SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
}

void TagLineEdit::onTextEdited(const QString &arg1)
{
    QString arg = arg1;
    arg = arg.replace(' ', '-');
    arg = arg.toLower();
    setText(arg);
}
