#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QListWidget>

class TagListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit TagListWidget(QWidget *parent = 0);

    QStringList toStringList();
signals:

public slots:
    void showContextMenu(const QPoint&);
    void removeSelectedItem();

};

#endif // TAGLISTWIDGET_H
