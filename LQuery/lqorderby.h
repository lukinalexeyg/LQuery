#ifndef LQORDERBY_H
#define LQORDERBY_H

#pragma once

#include "lqexpression.h"

class LQOrderBy
{
public:
    static LQOrderBy expression(const LQExpression &expression);
    static LQOrderBy expression(const QString &sql);
    LQOrderBy &collate(const QString &collation);
    LQOrderBy &desc();
    QString make() const;

private:
    LQOrderBy(const QString &sql);

private:
    QString m_expression;
    QString m_collation;
    bool m_desc = false;
};

#endif // LQORDERBY_H
