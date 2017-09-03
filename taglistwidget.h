#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QListWidget>

class TagListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TagListWidget(QWidget *parent = 0);

    void addTagItem(const QString &tag);

    QStringList toStringList();

signals:

public slots:
    void showContextMenu(const QPoint&);
    void removeSelectedItem();

signals:
    void tagListAddition();
    void tagListDeletion();
};

#endif // TAGLISTWIDGET_H
