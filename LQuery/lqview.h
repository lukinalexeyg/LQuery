#ifndef LQVIEW_H
#define LQVIEW_H

#pragma once

#include <QVariant>

class LQView
{
public:
    static LQView create(const QString &entity);

    LQView &temp();
    LQView &if_not_exists();

    LQView &column(const QString &column);
    LQView &columns(const QStringList &columns);

    LQView &as(const QString &sql);

    QString make();

private:
    LQView(const QString &name);

private:
    QString m_entity;
    bool m_temp = false;
    bool m_if_not_exists = false;

    QStringList m_columns;

    QString m_select;
};

#endif // LQVIEW_H
