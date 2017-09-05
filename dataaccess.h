#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QtSql/QSqlDatabase>

class DataAccess
{
public:
    DataAccess(const QString dbname = "tags.sqlite");

    void OpenOrCreate();
    void InsertOrUpdate(const QString &item, const QStringList &tagList);
    QStringList QueryTags(const QStringList &tagList);
    QStringList QueryFile(const QString &fileName);
    QStringList BrowseTags();

private:
    void ExecQuery(const QString &string);
    int ExecScalar(const QString &string);
    QStringList ExecReader(const QString &string);

    void CreateItemsTable();
    void CreateTagsTable();
    void CreateItemTagMapTable();

    void InsertItem(const QString &item);
    void InsertTag(const QString &tag);
    void InsertMapping(int itemID, int tagID);

    int GetItemID(const QString &item);
    int GetTagID(const QString &tag);

private:
    QSqlDatabase m_db;
    QString m_dbname;
};

#endif // DATAACCESS_H
