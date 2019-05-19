#include "lqlimit.h"



LQLimit::LQLimit(const QString &limit, const QString &offset) :
    m_limit(limit),
    m_offset(offset)
{
}



LQLimit LQLimit::limit(int value0, int value1)
{
    QString _limit;
    QString _offset;

    if (value1 <= 0)
        _limit = QString::number(value0);
    else {
        _limit = QString::number(value1);
        _offset = QString::number(value0);
    }

    return LQLimit(_limit, _offset);
}



LQLimit LQLimit::limit(const LQExpression &expression)
{
    return LQLimit(expression.make());
}



LQLimit LQLimit::limit(const QString &sql)
{
    return LQLimit(sql);
}



LQLimit &LQLimit::offset(int value)
{
    m_offset = QString::number(value);
    return *this;
}



LQLimit &LQLimit::offset(const LQExpression &expression)
{
    m_offset = expression.make();
    return *this;
}



LQLimit &LQLimit::offset(const QString &sql)
{
    m_offset = sql;
    return *this;
}



QString LQLimit::make() const
{
    QStringList sql;

    if (!m_limit.isEmpty()) {
        sql << "LIMIT" << m_limit;

        if (!m_offset.isEmpty())
            sql << "OFFSET" << m_offset;
    }

    return sql.join(' ');
}
