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
    void setBusname();
    void setOrigin();
    void setDest();
    void setType();
    void updateBus();
};

#endif // BUS_H
