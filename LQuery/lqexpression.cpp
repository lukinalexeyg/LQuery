#include "lqexpression.h"



LQExpression::LQExpression(const QString &sql) :
    m_expression(sql)
{
}



LQExpression LQExpression::text(const QString &expression)
{
    return LQExpression(expression);
}



LQExpression &LQExpression::value(const QVariant &value)
{
    m_values << value;
    return *this;
}



LQExpression &LQExpression::values(const QVariantList &values)
{
    m_values << values;
    return *this;
}



QString LQExpression::make() const
{
    QString result = m_expression;

    if (!m_expression.isEmpty())
        for (const QVariant &value : qAsConst(m_values)) {
            const QString _value = value.toString().replace("'", "''");
            result.replace(result.indexOf('?'), 1, QString("'%1'").arg(_value));
        }

    return result;
}
