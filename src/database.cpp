#include "database.h"
#include <QDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

Database* Database::instance = 0;

Database::Database()
{
    dbpath = QString("database.db");
    bus_types = (QStringList() << "AC" << "Non-AC");
    connect();
    createBusTable();
    createLocTable();
    createTicketTable();
}

Database* Database::getInstance() {
    if (instance == 0)
        instance = new Database();
    return instance;
}

// connect with the database
void Database::connect() {
    const QString DRIVER("QSQLITE");
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(dbpath);

    if (!db.open())
        qDebug() << "ERROR: " << db.lastError();
    else
        qDebug() << "Database Connected";
}


// disconnect from database, must be called when database operation completes
void Database::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database disconnected";
    }

}


// create the bus table
void Database::createBusTable() {
    qDebug() << "Creating bus table";
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS BUS (BUSNAME TEXT PRIMARY KEY, ORIGIN TEXT, DEST TEXT, TYPE TEXT)");

    if (!query.exec())
        qDebug() << query.lastError().text();
    else
        qDebug() << "table BUS created";

}

// create the ticket table
void Database::createTicketTable() {
    qDebug() << "Creating Ticket";
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS TICKET (PASSENGERNAME TEXT, BUSNAME TEXT, DATE TEXT, SEAT_NO INTEGER)");

    if (!query.exec())
        qDebug() << query.lastError().text();
    else
        qDebug() << "Ticket table created";

}


//Inserting Bus
void Database::insertBus(QString busname, QString origin, QString dest, QString type) {
    QSqlQuery query;
    query.prepare("INSERT INTO BUS VALUES(?, ?, ?, ?)");
    query.addBindValue(busname);
    query.addBindValue(origin);
    query.addBindValue(dest);
    query.addBindValue(type);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
    else
        {
            qDebug() << "Bus " << busname << " created";
        }
}

//Removing Bus
void Database::removeBus(QString busname) {
    QSqlQuery query;
    query.prepare("DELETE FROM BUS WHERE BUSNAME=?");
    query.addBindValue(busname);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
    else
        {
            qDebug() << "Bus " << busname << " deleted";
        }
}

//Edit Bus
void Database::editBus(QString busname, QString origin, QString dest, QString type) {
    QSqlQuery query;
    query.prepare("UPDATE BUS SET ORIGIN = ?, DEST = ?, TYPE = ? WHERE BUSNAME = ?;");
    query.addBindValue(origin);
    query.addBindValue(dest);
    query.addBindValue(type);
    query.addBindValue(busname);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
    else
        {
            qDebug() << "Bus " << busname << " edited";
        }
}


// create the location table (required for origin/desination)
void Database::createLocTable() {
    qDebug() << "Creating LOCATIONS table";
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS LOCATIONS (LOCNAME TEXT PRIMARY KEY)");

    if (!query.exec())
        qDebug() << query.lastError().text();
    else
        qDebug() << "table LOCATIONS created";

}


// insert location
void Database::insertLocation(QString locname) {
    qDebug() << "inserting started";
    QSqlQuery query;
    query.prepare("INSERT INTO LOCATIONS VALUES(?)");
    query.addBindValue(locname);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
    else
        qDebug() << "location " << locname << " inserted";
}


// load location
void Database::getLocations() {
    QSqlQuery query;
    locations.clear();
    query.prepare("SELECT * FROM LOCATIONS ORDER BY LOCNAME");

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();

    while (query.next())
        locations.append(query.value(0).toString());
}

// get bus list
void Database::getBuses() {
    QSqlQuery query;
    buses.clear();
    query.prepare("SELECT * FROM BUS");

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();

    while (query.next()) {
        // do something
    }
}
// delete a location record
void Database::removeLoc(QString locname) {
    QSqlQuery query;
    query.prepare("DELETE FROM LOCATIONS WHERE LOCNAME = ?");
    query.addBindValue(locname);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
}
