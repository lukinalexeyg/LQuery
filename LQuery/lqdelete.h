#ifndef LQDELETE_H
#define LQDELETE_H

#pragma once

#include "lqorderby.h"
#include "lqlimit.h"

class LQDelete
{
public:
    static LQDelete delete_from(const QString &entity);

    LQDelete &where(const LQExpression &expression);
    LQDelete &where(const QString &sql);

    LQDelete &order_by(const LQOrderBy &orderBy);
    LQDelete &order_by(const QString &sql);

    LQDelete &limit(int value0, int value1 = 0);
    LQDelete &limit(const LQLimit &limit);
    LQDelete &limit(const QString &sql);

    QString make();

private:
    LQDelete(const QString &entity);

private:
    QString m_entity;
    QString m_where;
    QStringList m_order_by;
    QString m_limit;
};

#endif // LQDELETE_H
