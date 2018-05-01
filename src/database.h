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
    void insertTicket(QString pname, QString gender, QString mobno,
                      QString bname, QString from, QString to, QString date, QString seat);
    void getLocations();
    void insertBus(QString busname, QString origin, QString dest, QString type);
    void removeBus(QString busname);
    void editBus(QString busname, QString origin, QString dest, QString type);
    void removeLoc(QString locname);
    void getBuses();
    QStringList locations;
    QStringList bus_types;
    QVector<Bus*> buses;
    QList<Bus> getBusByTripInfo(QString from, QString to, QString type);
    // void createBus(QString busname, QString origin, QString dest, QString type);

private:
    static Database* instance;
    Database();
    QSqlDatabase db;
    QString dbpath;
};

#endif // DATABASE_H
