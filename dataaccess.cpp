#include "dataaccess.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

DataAccess::DataAccess()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

void DataAccess::OpenOrCreate()
{
    m_db.setDatabaseName("hello.sqlite");
    bool opened = m_db.open();

    if (opened)
        qDebug() << QString("Database open succeeded.");
    else
        qDebug() << QString("Database open failed.");

    CreateItemsTable();
    CreateTagsTable();
    CreateItemTagMapTable();
}

void DataAccess::InsertOrUpdate(const QString &item, const QStringList &tagList)
{
    if (tagList.isEmpty())
        return;

    // TODO: begin transaction

    InsertItem(item);
    int itemID = GetItemID(item);

    for (QString tag : tagList)
    {
        InsertTag(tag);
        int tagID = GetTagID(tag);

        if (itemID >= 0 && tagID >= 0)
        {
            InsertMapping(itemID, tagID);
        }
    }

    // TODO: end transaction
}

QString toCsv(const QStringList &tagList)
{
    QString csv;
    for (QString tag : tagList)
        csv.append(QString("\'%1\',").arg(tag));
    if (csv.endsWith(','))
        csv.chop(1);

    return csv;
}

QStringList DataAccess::QueryTags(const QStringList &tagList)
{
    QString csv = toCsv(tagList);
    QString string = QString("SELECT `content` "
                             "FROM `items` "
                             "INNER JOIN `item_tag_map` ON items.id=item_tag_map.item_id "
                             "INNER JOIN tags ON tags.id=item_tag_map.tag_id "
                             "WHERE tags.title IN (%1)").arg(csv);

    QStringList result;
    QSqlQuery query(string);
    while (query.next())
        result.push_back(query.value(0).toString());

    return result;
}

void DataAccess::ExecQuery(const QString &string)
{
    if (m_db.isOpen())
    {
        QSqlQuery query;
        query.exec(string);
        if (query.lastError().isValid())
        {
            QMessageBox::critical(0, "Database error", query.lastError().text());
        }
    }
}

int DataAccess::ExecScalar(const QString &string)
{
    QSqlQuery query(string);
    if (query.next())
        return query.value(0).toInt();
    else
        return -1;
}

void DataAccess::CreateItemsTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS `items` ( "
                    "`id` integer PRIMARY KEY, "
                    "`content` varchar(256) NOT NULL default '' );";
    ExecQuery(query);
}

void DataAccess::CreateTagsTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS `tags` ( "
                    "`id` integer PRIMARY KEY, "
                    "`title` varchar(45) NOT NULL default '' );";
    ExecQuery(query);
}

void DataAccess::CreateItemTagMapTable()
{
    QString query = "CREATE TABLE IF NOT EXISTS `item_tag_map` ( "
                    "`item_id` integer NOT NULL default '0', "
                    "`tag_id` integer NOT NULL default '0', "
                    "PRIMARY KEY  (`item_id`,`tag_id`), "
                    "CONSTRAINT `item_fk` FOREIGN KEY (`item_id`) REFERENCES `items` (`item_id`), "
                    "CONSTRAINT `tag_fk` FOREIGN KEY (`tag_id`) REFERENCES `tags` (`tag_id`) );";
    ExecQuery(query);
}

void DataAccess::InsertItem(const QString &item)
{
    QString query = QString("INSERT INTO `items` (`content`) "
                            "SELECT '%1' "
                            "WHERE NOT EXISTS ("
                            "SELECT 1 FROM `items` "
                            "WHERE `content` = '%2');").arg(item).arg(item);
    ExecQuery(query);
}

void DataAccess::InsertTag(const QString &tag)
{
    QString query = QString("INSERT INTO `tags` (`title`) "
                            "SELECT '%1' "
                            "WHERE NOT EXISTS ("
                            "SELECT 1 FROM `tags` "
                            "WHERE `title` = '%2' );").arg(tag).arg(tag);
    ExecQuery(query);
}

void DataAccess::InsertMapping(int itemID, int tagID)
{
    QString query = QString("INSERT INTO `item_tag_map` "
                            "VALUES (%1, %2);").arg(itemID).arg(tagID);
    ExecQuery(query);
}

int DataAccess::GetItemID(const QString &item)
{
    QString string = QString("SELECT `id` FROM `items` "
                             "WHERE `content` = '%1'").arg(item);
    return ExecScalar(string);
}

int DataAccess::GetTagID(const QString &tag)
{
    QString string = QString("SELECT `id` FROM `tags` "
                             "WHERE `title` = '%1'").arg(tag);
    return ExecScalar(string);
}

/*
SELECT last_insert_rowid();

-- show tags for a given filename

SELECT title
FROM tags
INNER JOIN item_tag_map ON tags.id=item_tag_map.tag_id
INNER JOIN items ON items.id=item_tag_map.item_id
WHERE items.content='H:\Storm\Infraburo'

*/
