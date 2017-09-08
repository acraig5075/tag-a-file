#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QtSql/QSqlDatabase>

class QSqlQueryModel;

class DataAccess
{
public:
    DataAccess(const QString dbname = "tags.sqlite");

    void OpenOrCreate();
    void InsertOrUpdate(const QString &item, const QStringList &tagList);

    QStringList GetTagsForItem(const QString &content);
    QString GetItemContent(int id);
    QString GetTagTitle(int id);
    int GetItemID(const QString &item);
    int GetTagID(const QString &tag);
    void SetItemContent(int id, const QString &content);
    void SetTagTitle(int id, const QString &title);

    void RefreshSearchModel(QSqlQueryModel &model, const QStringList &tagList);
    void RefreshItemsModel(QSqlQueryModel &model);
    void RefreshTagsModel(QSqlQueryModel &model);

    void DeleteItem(int id);
    void DeleteTag(int id);

private:
    void ExecQuery(const QString &string);
    int ExecScalar(const QString &string);
    QString ExecScalarString(const QString &string);
    QStringList ExecReader(const QString &string);

    void CreateItemsTable();
    void CreateTagsTable();
    void CreateItemTagMapTable();

    void InsertItem(const QString &item);
    void InsertTag(const QString &tag);
    void InsertMapping(int itemID, int tagID);
    void InsertMappings(int itemID, const QList<int> &tagIDs);
    void DeleteMappings(int itemID);

private:
    QSqlDatabase m_db;
    QString m_dbname;
};

#endif // DATAACCESS_H
