#ifndef LQINSERT_H
#define LQINSERT_H

#pragma once

#include <QVariant>

class LQInsert
{
public:
    enum Type {
        Insert,
        Replace,
        InsertOrReplace,
        InsertOrRollback,
        InsertOrAbort,
        InsertOrFail,
        InsertOrIgnore
    };

public:
    static LQInsert insert_into(const QString &entity, Type type = Insert);

    LQInsert &values(const QMap<QString, QVariant> &values);

    LQInsert &column(const QString &column);
    LQInsert &columns(const QStringList &columns);

//    LQInsert &row(const QVariant &value);
    LQInsert &row(const QVariantList &values);
    LQInsert &rows(const QList<QVariantList> &values);

    LQInsert &sub_select(const QString &sql);

    LQInsert &upsert(const QString &sql); // TODO LQUpsert

    QString make();

    LQInsert &operator=(const LQInsert &);

private:
    const QStringList TypeStrings = {
        "INSERT",
        "REPLACE",
        "INSERT OR REPLACE",
        "INSERT OR ROLLBACK",
        "INSERT OR ABORT",
        "INSERT OR FAIL",
        "INSERT OR IGNORE"
    };

private:
    LQInsert(const QString &entity, Type type);

private:
    QString m_entity;
    Type m_type;

    QStringList m_columns;
    QList<QVariantList> m_rows;
    QList<QMap<QString, QVariant>> m_values;

    QString m_sub_select;

    QString m_upsert;
};

#endif // LQINSERT_H
