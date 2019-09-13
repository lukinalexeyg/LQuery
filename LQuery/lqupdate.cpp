#include "lqupdate.h"



LQUpdate::LQUpdate(const QString &entity, LQUpdate::Type type) :
    m_entity(entity),
    m_type(type)
{
}



LQUpdate &LQUpdate::operator=(const LQUpdate &)
{
    return *this;
}



LQUpdate LQUpdate::update(const QString &entity, LQUpdate::Type type)
{
    return LQUpdate(entity.trimmed(), type);
}



LQUpdate &LQUpdate::set(const QString &column, const QVariant &value)
{
    m_values.insert(column.trimmed(), value);
    return *this;
}



LQUpdate &LQUpdate::set(const QMap<QString, QVariant> &values)
{
    for (const QString &key: values.keys())
        m_values.insert(key, values.value(key));
    return *this;
}



LQUpdate &LQUpdate::where(const LQExpression &expression)
{
    m_where = expression.make();
    return *this;
}



LQUpdate &LQUpdate::where(const QString &sql)
{
    m_where = sql;
    return *this;
}



LQUpdate &LQUpdate::order_by(const LQOrderBy &orderBy)
{
    m_order_by << orderBy.make();
    return *this;
}



LQUpdate &LQUpdate::order_by(const QString &sql)
{
    m_order_by << sql;
    return *this;
}



LQUpdate &LQUpdate::limit(int value0, int value1)
{
    m_limit = LQLimit::limit(value0, value1).make();
    return *this;
}



LQUpdate &LQUpdate::limit(const LQLimit &limit)
{
    m_limit = limit.make();
    return *this;
}



LQUpdate &LQUpdate::limit(const QString &sql)
{
    m_limit = sql;
    return *this;
}



QString LQUpdate::make()
{
    QStringList sql;

    sql << TypeStrings.at(m_type);

    sql << m_entity;

    if (!m_values.isEmpty()) {
        QStringList values;
        for (const QString &key : m_values.keys()) {
            const QString value = m_values.value(key).toString().replace("'", "''");
            values << QString("%1 = '%2'")
                      .arg(key)
                      .arg(value);
        }
        sql << "SET" << values.join(", ");
    }

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
