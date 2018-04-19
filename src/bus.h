#ifndef BUS_H
#define BUS_H
#include <QString>


class Bus
{
public:
    Bus(QString _busname, QString _origin, QString _dest, QString _type);
    QString busname;
    QString origin;
    QString dest;
    QString type;
};

#endif // BUS_H