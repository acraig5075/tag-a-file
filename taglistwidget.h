#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QListWidget>

class TagListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TagListWidget(QWidget *parent = 0);

    void addTagItem(const QString &tag);
    void addTagItems(const QStringList &tags);

    QStringList toStringList();

signals:

public slots:
    void showContextMenu(const QPoint&);
    void removeSelectedItem();
    void removeAllItems();

signals:
    void tagListAddition();
    void tagListDeletion();
};

#endif // TAGLISTWIDGET_H
