# LQuery
LQuery - набор классов для более удобного создания SQLite-запросов.
## Примеры:
+ Создание таблицы
```C++
const QString sql = LQTable::create("table")
    .if_not_exists()
    .column(LQColumn::name("id").type(LQColumn::Integer).not_null().unique().autoincrement().primary_key())
    .column(LQColumn::name("name").type(LQColumn::Text).not_null())
    .column(LQColumn::name("timestamp").type(LQColumn::Text).not_null().def(LQColumn::CurrentTimestamp))
    .column(LQColumn::name("value_0").type(LQColumn::Integer).not_null().def("0"))
    .column(LQColumn::name("value_1").type(LQColumn::Integer).def(LQColumn::Null))
    .make();
```
```SQL
CREATE TABLE IF NOT EXISTS table ('id' INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL ON CONFLICT ABORT UNIQUE ON CONFLICT ABORT, 'name' TEXT NOT NULL ON CONFLICT ABORT, 'timestamp' TEXT NOT NULL ON CONFLICT ABORT DEFAULT CURRENT_TIMESTAMP, 'value_0' INTEGER NOT NULL ON CONFLICT ABORT DEFAULT 0, 'value_1' INTEGER DEFAULT NULL)
```
