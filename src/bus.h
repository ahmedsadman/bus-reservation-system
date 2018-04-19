#ifndef BUS_H
#define BUS_H
#include <QString>

class Bus
{
 private:
    QString busname;
    QString origin;
    QString dest;
    QString type;

public:
    Bus(QString _busname, QString _origin, QString _dest, QString _type);
    QString getBusname();
    QString getOrigin();
    QString getDest();
    QString getType();
    void setBusname(QString _busname);
    void setOrigin(QString _origin);
    void setDest(QString _dest);
    void setType(QString _type);
    void updateBus();
};

#endif // BUS_H
