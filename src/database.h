#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QVector>
#include "bus.h"

class Database
{
public:
    static Database* getInstance(); // singleton
    void connect();
    void disconnect();
    void createBusTable();
    void createTicketTable();
    void createLocTable();
    void insertLocation(QString locname);
    void getLocations();
    void insertBus(Bus a);
    void removeBus(QString busname);
    void editBus(Bus a);
    void removeLoc(QString locname);

    QStringList locations;
    QStringList bus_types;
    // void createBus(QString busname, QString origin, QString dest, QString type);

private:
    static Database* instance;
    Database();
    QSqlDatabase db;
    QString dbpath;
};

#endif // DATABASE_H
