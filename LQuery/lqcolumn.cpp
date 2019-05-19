#include "lqcolumn.h"



LQColumn::LQColumn(const QString &name) :
    m_name(name)
{
}



LQColumn LQColumn::name(const QString &name)
{
    return LQColumn(name.simplified());
}



LQColumn &LQColumn::type(LQColumn::Type type)
{
    m_type = TypesString.at(type);
    return *this;
}



LQColumn &LQColumn::type(const QString &type)
{
    m_type = type.simplified();
    return *this;
}



//LQColumn &LQColumn::primary_key(OnConflict onConflict, bool autoincrement, bool asc)
LQColumn &LQColumn::primary_key(OnConflict onConflict)
{
//    QStringList constraint;
//    constraint << "PRIMARY KEY";

//    if (asc)
//        constraint << "ASC";

//    constraint << OnConflictStrings.at(onConflict);

//    if (autoincrement)
//        constraint << "AUTOINCREMENT";

//    m_constraints << constraint.join(' ');

    m_primary_key_onConflict = OnConflictStrings.at(onConflict);
    return *this;
}



LQColumn &LQColumn::autoincrement(bool asc)
{
    m_primary_key_autoincrement = true;
    m_primary_key_asc = asc;
    return *this;
}



LQColumn &LQColumn::not_null(OnConflict onConflict)
{
    QStringList constraint;
    constraint << "NOT NULL";
    constraint << OnConflictStrings.at(onConflict);
    m_constraints << constraint.join(' ');

    return *this;
}



LQColumn &LQColumn::unique(OnConflict onConflict)
{
    QStringList constraint;
    constraint << "UNIQUE";
    constraint << OnConflictStrings.at(onConflict);
    m_constraints << constraint.join(' ');

    return *this;
}



LQColumn &LQColumn::check(const LQExpression &expression)
{
    return check(expression.make());
}



LQColumn &LQColumn::check(const QString &sql)
{
    QStringList constraint;
    constraint << "CHECK";

    if (!sql.isEmpty())
        constraint << QString("(%1)").arg(sql);

    m_constraints << constraint.join(' ');

    return *this;
}



LQColumn &LQColumn::def(DefaultValue value)
{
    return def(DefaultValuesString.at(value));
}



LQColumn &LQColumn::def(const LQExpression &expression)
{
    return def(expression.make());
}



LQColumn &LQColumn::def(const QVariant &value)
{
    return def(value.toString());
}



LQColumn &LQColumn::def(const QString &value)
{
    if (!value.isEmpty()) {
        QStringList constraint;
        constraint << "DEFAULT";
        constraint << value;
        m_constraints << constraint.join(' ');
    }

    return *this;
}



LQColumn &LQColumn::collate(const QString &collation)
{
    QStringList constraint;
    constraint << "COLLATE";

    if (!collation.isEmpty())
        constraint << collation.simplified();

    m_constraints << constraint.join(' ');

    return *this;
}



LQColumn &LQColumn::foreign_key(const QString &key)
{
    m_constraints << key.simplified();
    return *this;
}



QString LQColumn::make() const
{
    QStringList sql;

    if (!m_name.isEmpty())
        sql << QString("'%1'").arg(m_name);

    if (!m_type.isEmpty())
        sql << m_type;

    if (!m_primary_key_onConflict.isEmpty()) {
        sql << "PRIMARY KEY";

        if (m_primary_key_autoincrement) {
            if (m_primary_key_asc)
                sql << "ASC";
            else
                sql << "DESC";
            sql << "AUTOINCREMENT";
        }
    }

    if (!m_constraints.isEmpty())
        sql << m_constraints.join(' ');

    return sql.join(' ');
}
