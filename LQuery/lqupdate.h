#ifndef LQUPDATE_H
#define LQUPDATE_H

#pragma once

#include "lqorderby.h"
#include "lqlimit.h"

class LQUpdate
{
public:
    enum Type {
        Update,
        UpdateOrRollback,
        UpdateOrAbort,
        UpdateOrReplace,
        UpdateOrFail,
        UpdateOrIgnore
    };

public:
    static LQUpdate update(const QString &entity, Type type = Update);

    LQUpdate &set(const QString &column, const QVariant &value);
    LQUpdate &set(const QMap<QString, QVariant> &values);

    LQUpdate &where(const LQExpression &expression);
    LQUpdate &where(const QString &sql);

    LQUpdate &order_by(const LQOrderBy &orderBy);
    LQUpdate &order_by(const QString &sql);

    LQUpdate &limit(int value0, int value1 = 0);
    LQUpdate &limit(const LQLimit &limit);
    LQUpdate &limit(const QString &sql);

    QString make();

    LQUpdate &operator=(const LQUpdate &);

private:
    const QStringList TypeStrings = {
        "UPDATE",
        "UPDATE OR ROLLBACK",
        "UPDATE OR ABORT",
        "UPDATE OR REPLACE",
        "UPDATE OR FAIL",
        "UPDATE OR IGNORE"
    };

private:
    LQUpdate(const QString &entity, Type type);

private:
    QString m_entity;
    Type m_type;
    QMap<QString, QVariant> m_values;
    QString m_where;
    QStringList m_order_by;
    QString m_limit;
};

#endif // LQUPDATE_H
