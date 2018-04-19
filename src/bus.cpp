#include "bus.h"
#include "database.h"


Bus::Bus(QString _busname, QString _origin, QString _dest, QString _type)
{
    busname = _busname;
    origin = _origin;
    dest = _dest;
    type = _type;
}

QString Bus::getBusname()
{
   return busname;

};


QString Bus::getOrigin()
{
    return origin;

};

QString Bus::getDest()
{
    return dest;

};

QString Bus::getType()
{

    return type;
};

void Bus::setBusname(QString _busname)
{
    busname=_busname;

};

void Bus::setOrigin(QString _origin)
{
    origin=_origin;

};

void Bus::setDest(QString _dest)
{
    dest=_dest;

};

void Bus::setType(QString _type)
{
    type=_type;

};

void Bus::updateBus()
{
    Database *db;
    db = Database::getInstance();
    db->editBus(busname, origin, dest, type);
}
