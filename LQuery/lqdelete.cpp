#include "lqdelete.h"



LQDelete::LQDelete(const QString &entity) :
    m_entity(entity)
{
}



LQDelete LQDelete::delete_from(const QString &entity)
{
    return LQDelete(entity.trimmed());
}



LQDelete &LQDelete::where(const LQExpression &where)
{
    m_where = where.make();
    return *this;
}



LQDelete &LQDelete::where(const QString &sql)
{
    m_where = sql;
    return *this;
}



LQDelete &LQDelete::order_by(const LQOrderBy &orderBy)
{
    m_order_by << orderBy.make();
    return *this;
}



LQDelete &LQDelete::order_by(const QString &sql)
{
    m_order_by << sql.trimmed();
    return *this;
}



LQDelete &LQDelete::limit(int value0, int value1)
{
    m_limit = LQLimit::limit(value0, value1).make();
    return *this;
}



LQDelete &LQDelete::limit(const LQLimit &limit)
{
    m_limit = limit.make();
    return *this;
}



LQDelete &LQDelete::limit(const QString &sql)
{
    m_limit = sql;
    return *this;
}



QString LQDelete::make()
{
    QStringList sql;

    sql << "DELETE FROM";

    if (!m_entity.isEmpty())
        sql << m_entity;

    if (!m_where.isEmpty())
        sql << "WHERE" << m_where;

    if (!m_order_by.isEmpty()) {
        const QString order_by = m_order_by.join(", ");
        if (!order_by.toUpper().startsWith("ORDER BY"))
            sql << "ORDER BY";
        sql << order_by;
    }

    if (!m_limit.isEmpty()) {
        if (!m_limit.toUpper().startsWith("LIMIT"))
            sql << "LIMIT";
        sql << m_limit;
    }

    return sql.join(' ');
}
