#ifndef LQCOLUMN_H
#define LQCOLUMN_H

#pragma once

#include "lqexpression.h"

class LQColumn
{
public:
    enum Type {
        None,
        Integer,
        Real,
        Text,
        Blob
    };

    enum OnConflict {
        OnConflictRollback,
        OnConflictAbort,
        OnConflictFail,
        OnConflictIgnore,
        OnConflictReplace
    };

    enum DefaultValue {
        Null,
        True,
        False,
        CurrentTime,
        CurrentDate,
        CurrentTimestamp
    };

public:
    static LQColumn name(const QString &name);

    LQColumn &type(Type type);
    LQColumn &type(const QString &type);

//    LQColumn &primary_key(OnConflict onConflict = OnConflictAbort, bool autoincrement = true, bool asc = true);
    LQColumn &primary_key(OnConflict onConflict = OnConflictAbort);
    LQColumn &autoincrement(bool asc = true);

    LQColumn &not_null(OnConflict onConflict = OnConflictAbort);

    LQColumn &unique(OnConflict onConflict = OnConflictAbort);

    LQColumn &check(const LQExpression &expression);
    LQColumn &check(const QString &sql);

    LQColumn &def(DefaultValue value);
    LQColumn &def(const LQExpression &expression);
    LQColumn &def(const QVariant &value);
    LQColumn &def(const QString &value);

    LQColumn &collate(const QString &collation);

    LQColumn &foreign_key(const QString &key); // TODO LQForeignKey

    QString make() const;

private:
    const QStringList TypesString = {
        "NULL",
        "INTEGER",
        "REAL",
        "TEXT",
        "BLOB"
    };

    const QStringList OnConflictStrings = {
        "ON CONFLICT ROLLBACK",
        "ON CONFLICT ABORT",
        "ON CONFLICT FAIL",
        "ON CONFLICT IGNORE",
        "ON CONFLICT REPLACE"
    };

    const QStringList DefaultValuesString = {
        "NULL",
        "TRUE",
        "FALSE",
        "CURRENT_TIME",
        "CURRENT_DATE",
        "CURRENT_TIMESTAMP"
    };

private:
    LQColumn(const QString &name);

private:
    QString m_name;
    QString m_type;
    QStringList m_constraints;
    QString m_primary_key_onConflict;
    bool m_primary_key_autoincrement = false;
    bool m_primary_key_asc = true;
};

#endif // LQCOLUMN_H
