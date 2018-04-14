#include "database.h"
#include <QDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

Database::Database()
{
    dbpath = QString("database.db");
    connect();
}

Database::~Database() {
    if (db.isOpen())
        disconnect();
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
    db.close();
    qDebug() << "Database disconnected";
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


// create the location table (required for origin/desination)
void Database::createLocTable() {
    qDebug() << "Creating bus table";
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS LOCATIONS (LOCNAME TEXT PRIMARY KEY)");

    if (!query.exec())
        qDebug() << query.lastError().text();
    else
        qDebug() << "table LOCATIONS created";

}


// insert location
void Database::insertLocation(QString locname) {
    QSqlQuery query;
    query.prepare("INSERT INTO LOCATIONS VALUES(?)");
    query.addBindValue(locname);

    if (!query.exec())
        qDebug() << "ERROR: " << query.lastError().text();
    else
        qDebug() << "location " << locname << " inserted";
}
