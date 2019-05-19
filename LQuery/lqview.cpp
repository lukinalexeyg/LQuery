#include "lqview.h"



LQView::LQView(const QString &entity) :
    m_entity(entity)
{
}



LQView LQView::create(const QString &entity)
{
    return LQView(entity.simplified());
}



LQView &LQView::temp()
{
    m_temp = true;
    return *this;
}



LQView &LQView::if_not_exists()
{
    m_if_not_exists = true;
    return *this;
}



LQView &LQView::column(const QString &column)
{
    m_columns << column;
    return *this;
}



LQView &LQView::columns(const QStringList &columns)
{
    m_columns << columns;
    return *this;
}



LQView &LQView::as(const QString &sql)
{
    m_select = sql;
    return *this;
}



QString LQView::make()
{
    QStringList sql;

    sql << "CREATE";

    if (m_temp)
        sql << "TEMP";

    sql << "VIEW";

    if (m_if_not_exists)
        sql << "IF NOT EXISTS";

    if (!m_entity.isEmpty())
        sql << m_entity;

    if (!m_columns.isEmpty())
        sql << QString("(%1)").arg(m_columns.join(", "));

    if (!m_select.isEmpty())
        sql << "AS" << m_select;

    return sql.join(' ');
}
