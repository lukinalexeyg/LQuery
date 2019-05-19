#include "lqjoin.h"


LQJoin::LQJoin(Type type, const QString &entity) :
    m_type(type),
    m_entity(entity)
{
}



LQJoin LQJoin::inner(const QString &entity)
{
    return LQJoin(Inner, entity.simplified());
}



LQJoin LQJoin::left(const QString &entity)
{
    return LQJoin(Left, entity.simplified());
}



LQJoin LQJoin::cross(const QString &entity)
{
    return LQJoin(Cross, entity.simplified());
}



LQJoin &LQJoin::natural()
{
    m_natural = true;
    return *this;
}



LQJoin &LQJoin::on(const QString &expression)
{
    m_expression = expression;
    return *this;
}



LQJoin &LQJoin::using_(const QString &column)
{
    m_columns << column.simplified();
    return *this;
}



LQJoin &LQJoin::using_(const QStringList &columns)
{
    m_columns << columns;
    return *this;
}



QString LQJoin::make() const
{
    QStringList sql;

    if (m_natural)
        sql << "NATURAL";

    sql << JoinStrings.at(m_type);
    sql << "JOIN";
    sql << m_entity;

    if (!m_expression.isEmpty())
        sql << "ON" << m_expression;
    else if (m_columns.count() > 0)
        sql << QString("USING (%1)").arg(m_columns.join(", "));

    return sql.join(' ');
}
