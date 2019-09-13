#include "lqorderby.h"



LQOrderBy::LQOrderBy(const QString &sql) :
    m_expression(sql)
{
}



LQOrderBy LQOrderBy::expression(const LQExpression &expression)
{
    return LQOrderBy(expression.make());
}



LQOrderBy LQOrderBy::expression(const QString &sql)
{
    return LQOrderBy(sql);
}



LQOrderBy &LQOrderBy::collate(const QString &collation)
{
    m_collation = collation.trimmed();
    return *this;
}



LQOrderBy &LQOrderBy::desc()
{
    m_desc = true;
    return *this;
}



QString LQOrderBy::make() const
{
    QStringList sql;

    sql << "ORDER BY";
    sql << m_expression;

    if (!m_collation.isEmpty())
        sql << m_collation;

    if (m_desc)
        sql << "DESC";

    return sql.join(' ');
}
