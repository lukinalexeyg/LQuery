#ifndef LQSELECT_H
#define LQSELECT_H

#pragma once

#include "lqjoin.h"
#include "lqorderby.h"
#include "lqlimit.h"

class LQSelect
{
public:
    enum SelectType {
        Normal,
        SubQuery,
        Exists,
        NotExists
    };

    enum CompoundType {
        Union,
        UnionAll,
        Intersect,
        Except
    };

public:
    static LQSelect begin(SelectType type = Normal);

    LQSelect &select(const QString &sql);
    LQSelect &select(const QStringList &columns);

    LQSelect &distinct();

    LQSelect &from(const QString &entity, const QString &alias = QString()); // TODO

    LQSelect &join(const LQJoin &join);
    LQSelect &join(const QString &sql);

    LQSelect &where(const LQExpression &expression);
    LQSelect &where(const QString &sql);

    LQSelect &group_by(const LQExpression &expression);
    LQSelect &group_by(const QString &sql);

    LQSelect &having(const LQExpression &expression);
    LQSelect &having(const QString &sql);

    LQSelect &compound(CompoundType type = Union);

    LQSelect &order_by(const LQOrderBy &orderBy);
    LQSelect &order_by(const QString &sql);

    LQSelect &limit(int value0, int value1 = 0);
    LQSelect &limit(const LQLimit &limit);
    LQSelect &limit(const QString &sql);

    QString make();

private:
    LQSelect(SelectType type);
    void _make(QStringList &sql);

private:
    const QStringList TypePattern = { "%1", "(%1)", "SELECT EXISTS (%1)", "SELECT NOT EXISTS (%1)" };
    const QStringList CompoundStrings = { "UNION", "UNION ALL", "INTERSECT", "EXCEPT" };

private:
    QStringList m_result;
    SelectType m_type;
    QStringList m_what;
    bool m_distinct = false;
    QString m_from;
    QStringList m_join;
    QString m_where;
    QStringList m_group_by;
    QString m_having;
    QStringList m_order_by;
    QString m_limit;
};

#endif // LQSELECT_H
