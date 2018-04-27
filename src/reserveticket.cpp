#include "reserveticket.h"
#include "ui_reverseticket.h"

ReverseTicket::ReverseTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReverseTicket)
{
    ui->setupUi(this);
}

ReverseTicket::~ReverseTicket()
{
    delete ui;
}
