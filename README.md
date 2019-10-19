# LQuery
LQuery - набор классов для более удобного создания SQLite-запросов.
## Примеры:
+ Создание таблицы
```C++
const QString create_table_sql = LQTable::create("table")
    .if_not_exists()
    .column(LQColumn::name("id")        .type(LQColumn::Integer)    .not_null().unique().autoincrement().primary_key())
    .column(LQColumn::name("name")      .type(LQColumn::Text)       .not_null())
    .column(LQColumn::name("timestamp") .type(LQColumn::Text)       .not_null().def(LQColumn::CurrentTimestamp))
    .column(LQColumn::name("value_0")   .type(LQColumn::Integer)    .not_null().def("0"))
    .column(LQColumn::name("value_1")   .type(LQColumn::Integer)    .def(LQColumn::Null))
    .make();
```
```SQL
CREATE TABLE IF NOT EXISTS table ('id' INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL ON CONFLICT ABORT UNIQUE ON CONFLICT ABORT, 'name' TEXT NOT NULL ON CONFLICT ABORT, 'timestamp' TEXT NOT NULL ON CONFLICT ABORT DEFAULT CURRENT_TIMESTAMP, 'value_0' INTEGER NOT NULL ON CONFLICT ABORT DEFAULT 0, 'value_1' INTEGER DEFAULT NULL)
```
+ Добавление данных в таблицу
```C++
const QString insert_into_table_sql = LQInsert::insert_into("table")
    .columns(QStringList()  << "name"   << "timestamp"                                      << "value_0"    << "value_1")
    .row(QVariantList()     << "name_0" << QDateTime::currentDateTime().toSecsSinceEpoch()  << "value_0_0"  << "value_0_1")
    .row(QVariantList()     << "name_1" << QDateTime::currentDateTime().toSecsSinceEpoch()  << "value_1_0"  << "value_1_1")
    .make();
```
```SQL
INSERT INTO table (name, timestamp, value_0, value_1) VALUES ('name_0', '1571504162', 'value_0_0', 'value_0_1'), ('name_1', '1571504162', 'value_1_0', 'value_1_1')
```
