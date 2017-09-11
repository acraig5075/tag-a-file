#include "taglistwidget.h"
#include <QMenu>

TagListWidget::TagListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);

    QObject::connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
}

void TagListWidget::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Remove", this, SLOT(removeSelectedItem()));
    myMenu.addAction("Remove All", this, SLOT(removeAllItems()));

    myMenu.exec(globalPos);
}

void TagListWidget::addTagItem(const QString &tag)
{
    addItem(new QListWidgetItem(QIcon(":/price-tag.png"), tag, this));

    emit tagListAddition();
}

void TagListWidget::addTagItems(const QStringList &tags)
{
    for (const auto tag : tags)
        addItem(new QListWidgetItem(QIcon(":/price-tag.png"), tag, this));

    emit tagListAddition();
}

void TagListWidget::removeSelectedItem()
{
    QList<QListWidgetItem *> selection = selectedItems();
    if (!selection.isEmpty())
    {
        QListWidgetItem *item = selection[0];
        delete item;

        emit tagListDeletion();
    }
}

void TagListWidget::removeAllItems()
{
    clear();

    emit tagListDeletion();
}

QStringList TagListWidget::toStringList()
{
    QStringList tags;
    for (int i = 0; i < count(); ++i)
    {
        tags.push_back(item(i)->text());
    }

    return tags;
}
