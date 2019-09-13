#include <QVector>
#include "lqinsert.h"



LQInsert::LQInsert(const QString &entity, LQInsert::Type type) :
    m_entity(entity),
    m_type(type)
{
}



LQInsert &LQInsert::operator=(const LQInsert &)
{
    return *this;
}


LQInsert LQInsert::insert_into(const QString &entity, Type type)
{
    return LQInsert(entity.trimmed(), type);
}



LQInsert &LQInsert::values(const QMap<QString, QVariant> &values)
{
//    QMapIterator<QString, QVariant> it(values);
//    QVariantList row;

//    while (it.hasNext()) {
//        it.next();
//        if (!m_columns.contains(it.key()))
//            m_columns << it.key();
//        row << it.value();
//    }

//    m_rows << row;
    m_values << values;
    return *this;
}



LQInsert &LQInsert::column(const QString &column)
{
    if (!m_columns.contains(column.trimmed()))
        m_columns << column.trimmed();
    return *this;
}



LQInsert &LQInsert::columns(const QStringList &columns)
{
    m_columns << columns;
    return *this;
}



//LQInsert &LQInsert::row(const QVariant &value)
//{
//    return row(QVariantList() << value);
//}



LQInsert &LQInsert::row(const QVariantList &values)
{
    m_rows << values;
    return *this;
}



LQInsert &LQInsert::rows(const QList<QVariantList> &values)
{
    m_rows << values;
    return *this;
}



LQInsert &LQInsert::sub_select(const QString &sql)
{
    m_sub_select = sql;
    return *this;
}



LQInsert &LQInsert::upsert(const QString &sql)
{
    m_upsert = sql;
    return *this;
}



QString LQInsert::make()
{
    QStringList sql;

    sql << TypeStrings.at(m_type);
    sql << "INTO";

    if (!m_entity.isEmpty())
        sql << m_entity;

//    if (!m_rows.isEmpty() && !m_columns.isEmpty()) {
//        QStringList rowsString;

//        for (const QVariantList &row : qAsConst(m_rows)) {
//            QStringList rowString;
//            for (const QVariant &value : qAsConst(row))
//                rowString << QString("'%1'").arg(value.toString());
//            rowsString << QString("(%1)").arg(rowString.join(", "));
//        }

//        sql << QString("(%1)").arg(m_columns.join(", "));
//        sql << QString("VALUES %1").arg(rowsString.join(", "));
//    }

    if ((!m_columns.isEmpty() && !m_rows.isEmpty()) || !m_values.isEmpty()) {
        m_columns.removeDuplicates();
        for (const QMap<QString, QVariant> &map : qAsConst(m_values))
            for (const QString &key : map.keys())
                if (!m_columns.contains(key))
                    m_columns << key;

        QStringList rowsString;

        for (const QVariantList &row : qAsConst(m_rows)) {
            QStringList rowString;
            for (const QVariant &value : qAsConst(row))
                rowString << QString("'%1'").arg(value.toString());
            rowsString << QString("(%1)").arg(rowString.join(", "));
        }

        for (const QMap<QString, QVariant> &map : qAsConst(m_values)) {
            QVector<QString> rowVector(m_columns.count());

            QMapIterator<QString, QVariant> it(map);
            while (it.hasNext()) {
                it.next();
                const int index = m_columns.indexOf(it.key());
                const QString value = it.value().toString().replace("'", "''");
                rowVector[index] = QString("'%1'").arg(value);
            }

            const QStringList rowList = rowVector.toList();
            rowsString << QString("(%1)").arg(rowList.join(", "));
        }

        sql << QString("(%1)").arg(m_columns.join(", "));
        sql << QString("VALUES %1").arg(rowsString.join(", "));
    }

    else if (!m_sub_select.isEmpty())
        sql << m_sub_select;

    else
        sql << "DEFAULT VALUES";

    if (!m_upsert.isEmpty())
        sql << m_upsert;

    return sql.join(' ');
}
