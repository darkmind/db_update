# db_update

db_update is a tool to check schema consistency according to schema in json file and upgrade it with
SQL statements from json file.

## Requrements

cmake
Clang 4.0+ - compiler
[Mysql-Connector-C++](https://github.com/mysql/mysql-connector-cpp)
Boost

## Building

```
$ cmake ./
$ make
```

## Example

Initially you may want to create schema.json file of your schema:

```
$ db_update --host <IP> --user <User> --pass <Password> --db <DB name> --source_file schema.json --dump
Schema was dumped to schema.json
```

Before the update of database schema you can run check to be sure that current schema is equal to
the initial one in schema.json file.

```
$ db_update --host <IP> --user <User> --pass <Password> --db <DB name> --source_file schema.json --check
```
