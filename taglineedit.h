#ifndef TAGLINEEDIT_H
#define TAGLINEEDIT_H
#include <QLineEdit>

class QWidget;

class TagLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    TagLineEdit(QWidget *parent);

private slots:
    void onTextEdited(const QString &arg1);
};

#endif // TAGLINEEDIT_H
