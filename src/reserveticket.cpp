#include "reserveticket.h"
#include "ui_reserveticket.h"

ReserveTicket::ReserveTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReserveTicket)
{
    ui->setupUi(this);
}

ReserveTicket::~ReserveTicket()
{
    delete ui;
}
