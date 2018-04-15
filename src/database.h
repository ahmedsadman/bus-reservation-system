#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QVector>

class Database
{
public:
    static Database* getInstance(); // singleton
    void connect();
    void disconnect();
    void createBusTable();
    void createLocTable();
    void insertLocation(QString locname);
    void getLocations();
    void getBus(bus a);
    void removeLoc(QString locname);

    QVector<QString> locations;
    // void createBus(QString busname, QString origin, QString dest, QString type);

private:
    static Database* instance;
    Database();
    ~Database();
    QSqlDatabase db;
    QString dbpath;
};

#endif // DATABASE_H
