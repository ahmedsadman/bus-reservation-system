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
    void createTicketTable();
    void createLocTable();
    void insertLocation(QString locname);
    void getLocations();
    void insertBus(QString busname, QString origin, QString dest, QString type);
    void removeBus(QString busname);
    void editBus(QString busname, QString origin, QString dest, QString type);
    void removeLoc(QString locname);
    void getBuses();
    int AvaliableSeat(QString BusName, QString date, QString time);
    QStringList locations;
    QStringList bus_types;
    QStringList buses;
    // void createBus(QString busname, QString origin, QString dest, QString type);

private:
    static Database* instance;
    Database();
    QSqlDatabase db;
    QString dbpath;
};

#endif // DATABASE_H
