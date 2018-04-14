#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>

class Database
{
public:
    Database();
    ~Database();
    void connect();
    void disconnect();
    void createBusTable();
    void createLocTable();
    void insertLocation(QString locname);
    // void createBus(QString busname, QString origin, QString dest, QString type);

private:
    QSqlDatabase db;
    QString dbpath;
};

#endif // DATABASE_H
