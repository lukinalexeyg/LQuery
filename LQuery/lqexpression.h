#ifndef LQWHERE_H
#define LQWHERE_H

#pragma once

#include <QVariant>

class LQExpression
{
public:
    static LQExpression text(const QString &text);
    LQExpression &value(const QVariant &value);
    LQExpression &values(const QVariantList &values);
    QString make() const;

private:
    LQExpression(const QString &sql);

private:
    QString m_expression;
    QVariantList m_values;
};

#endif // LQWHERE_H
