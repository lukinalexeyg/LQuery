#ifndef LQJOIN_H
#define LQJOIN_H

#pragma once

#include <QVariant>

class LQJoin
{
public:
    static LQJoin inner(const QString &entity);
    static LQJoin left(const QString &entity);
    static LQJoin cross(const QString &entity);

    LQJoin &natural();

    LQJoin &on(const QString &expression);

    LQJoin &using_(const QString &column);
    LQJoin &using_(const QStringList &columns);

    QString make() const;

private:
    enum Type {
        Inner,
        Left,
        Cross
    };

    const QStringList JoinStrings = { "INNER", "LEFT", "CROSS" };

private:
    LQJoin(Type m_type, const QString &entity);

private:
    Type m_type;
    QString m_entity;
    bool m_natural = false;
    QString m_expression;
    QStringList m_columns;
};

#endif // LQJOIN_H
