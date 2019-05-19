#ifndef LQTABLE_H
#define LQTABLE_H

#pragma once

#include "lqcolumn.h"

class LQTable
{
public:
    static LQTable create(const QString &entity);

    LQTable &temp();
    LQTable &if_not_exists();

    LQTable &column(const LQColumn &column);
    LQTable &column(const QString &sql);

    LQTable &primary_key(const QString &sql); // TODO
    LQTable &unique(const QString &sql); // TODO

    LQTable &check(const LQExpression &expression);
    LQTable &check(const QString &sql);

    LQTable &foreign_key(const QString &key); // TODO

    LQTable &without_rowid();

    LQTable &as(const QString &sql);

    QString make();

private:
    LQTable(const QString &name);

private:
    QString m_entity;
    bool m_temp = false;
    bool m_if_not_exists = false;
    QStringList m_columns;

    QString m_primary_key;
    QString m_unique;
    QString m_check;
    QString m_foreign_key;

    QString m_select;
    bool m_without_rowid = false;
};

#endif // LQTABLE_H
