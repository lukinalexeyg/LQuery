#ifndef LQLIMIT_H
#define LQLIMIT_H

#pragma once

#include "lqexpression.h"

class LQLimit
{
public:
    static LQLimit limit(int value0, int value1 = 0);
    static LQLimit limit(const LQExpression &expression);
    static LQLimit limit(const QString &sql);

    LQLimit &offset(int value);
    LQLimit &offset(const LQExpression &expression);
    LQLimit &offset(const QString &sql);

    QString make() const;

private:
    LQLimit(const QString &limit, const QString &offset = QString());

private:
    QString m_limit;
    QString m_offset;
};

#endif // LQLIMIT_H
