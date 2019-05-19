#include "lqselect.h"



LQSelect::LQSelect(LQSelect::SelectType type) :
    m_type(type)
{
}



LQSelect LQSelect::begin(LQSelect::SelectType type)
{
    return LQSelect(type);
}



LQSelect &LQSelect::distinct()
{
    m_distinct = true;
    return *this;
}



LQSelect &LQSelect::select(const QString &sql)
{
    m_what << sql.simplified();
    return *this;
}



LQSelect &LQSelect::select(const QStringList &columns)
{
    m_what << columns;
    return *this;
}



LQSelect &LQSelect::from(const QString &entity, const QString &alias)
{
    m_from = QString("%1%2")
            .arg(entity)
            .arg(alias.isEmpty() ? "" : QString(" AS '%1'").arg(alias.simplified()));

    return *this;
}



LQSelect &LQSelect::join(const LQJoin &join)
{
    m_join << join.make();
    return *this;
}



LQSelect &LQSelect::join(const QString &sql)
{
    m_join << sql;
    return *this;
}



LQSelect &LQSelect::where(const LQExpression &expression)
{
    m_where = expression.make();
    return *this;
}



LQSelect &LQSelect::where(const QString &sql)
{
    m_where = sql;
    return *this;
}



LQSelect &LQSelect::group_by(const LQExpression &expression)
{
    m_group_by << expression.make();
    return *this;
}



LQSelect &LQSelect::group_by(const QString &sql)
{
    m_group_by << sql;
    return *this;
}



LQSelect &LQSelect::having(const LQExpression &expression)
{
    m_having = expression.make();
    return *this;
}



LQSelect &LQSelect::having(const QString &sql)
{
    m_having = sql;
    return *this;
}



LQSelect &LQSelect::compound(CompoundType type)
{
    QStringList sql;
    _make(sql);
    sql << CompoundStrings.at(type);
    m_result = sql;

    m_what.clear();
    m_distinct = false;
    m_from.clear();
    m_join.clear();
    m_where.clear();
    m_group_by.clear();
    m_having.clear();
    m_order_by.clear();
    m_limit.clear();

    return *this;
}



LQSelect &LQSelect::order_by(const LQOrderBy &orderBy)
{
    m_order_by << orderBy.make();
    return *this;
}



LQSelect &LQSelect::order_by(const QString &sql)
{
    m_order_by << sql;
    return *this;
}



LQSelect &LQSelect::limit(int value0, int value1)
{
    m_limit = LQLimit::limit(value0, value1).make();
    return *this;
}



LQSelect &LQSelect::limit(const LQLimit &limit)
{
    m_limit = limit.make();
    return *this;
}



LQSelect &LQSelect::limit(const QString &sql)
{
    m_limit = sql;
    return *this;
}



QString LQSelect::make()
{
    QStringList sql;

    _make(sql);

    if (!m_order_by.isEmpty() && m_type != Exists && m_type != NotExists) {
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

    return QString(TypePattern.at(m_type)).arg(sql.join(' '));
}



void LQSelect::_make(QStringList &sql)
{
    sql << m_result;

    sql << "SELECT";

    if (m_distinct)
        sql << "DISTINCT";

    if (!m_what.isEmpty())
        sql << m_what.join(", ");
    else
        sql << "*";

    if (!m_from.isEmpty() || !m_join.isEmpty()) {
        sql << "FROM";

        if (!m_from.isEmpty())
            sql << m_from;

        if (!m_join.isEmpty())
            sql << m_join.join(' ');
    }

    if (!m_where.isEmpty())
        sql << "WHERE" << m_where;

    if (!m_group_by.isEmpty())
        sql << "GROUP BY" << m_group_by.join(", ");

    if (!m_having.isEmpty())
        sql << "HAVING" << m_having;
}
