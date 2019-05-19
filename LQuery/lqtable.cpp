#include "lqtable.h"



LQTable::LQTable(const QString &entity) :
    m_entity(entity)
{
}



LQTable LQTable::create(const QString &entity)
{
    return LQTable(entity.simplified());
}



LQTable &LQTable::temp()
{
    m_temp = true;
    return *this;
}



LQTable &LQTable::if_not_exists()
{
    m_if_not_exists = true;
    return *this;
}



LQTable &LQTable::column(const LQColumn &column)
{
    m_columns << column.make();
    return *this;
}



LQTable &LQTable::column(const QString &sql)
{
    m_columns << sql;
    return *this;
}



LQTable &LQTable::primary_key(const QString &sql)
{
    m_primary_key = sql.simplified();
    return *this;
}



LQTable &LQTable::unique(const QString &sql)
{
    m_unique = sql.simplified();
    return *this;
}



LQTable &LQTable::check(const LQExpression &expression)
{
    m_check = expression.make();
    return *this;
}



LQTable &LQTable::check(const QString &sql)
{
    m_check = sql;
    return *this;
}



LQTable &LQTable::foreign_key(const QString &key)
{
    m_foreign_key = key.simplified();
    return *this;
}



LQTable &LQTable::as(const QString &sql)
{
    m_select = sql;
    return *this;
}



LQTable &LQTable::without_rowid()
{
    m_without_rowid = true;
    return *this;
}



QString LQTable::make()
{
    QStringList sql;

    sql << "CREATE";

    if (m_temp)
        sql << "TEMP";

    sql << "TABLE";

    if (m_if_not_exists)
        sql << "IF NOT EXISTS";

    if (!m_entity.isEmpty())
        sql << m_entity;

    if (!m_columns.isEmpty()) {
        QStringList constraints;

        constraints << m_columns.join(", ");

        if (!m_primary_key.isEmpty())
            constraints << QString("PRIMARY KEY (%1)").arg(m_primary_key);
        else if (!m_unique.isEmpty())
            constraints << QString("UNIQUE (%1)").arg(m_unique);

        if (!m_check.isEmpty())
            constraints << QString("CHECK (%1)").arg(m_check);

        if (!m_foreign_key.isEmpty())
            constraints << QString("FOREIGN KEY (%1)").arg(m_foreign_key);

        sql << QString("(%1)").arg(constraints.join(", "));

        if (m_without_rowid)
            sql << "WITHOUT ROWID";
    }
    else if (!m_select.isEmpty())
        sql << "AS" << m_select;

    return sql.join(' ');
}
