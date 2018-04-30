#include "reserveticket.h"
#include "ui_reserveticket.h"
#include <QDebug>
#include <QMessageBox>

ReserveTicket::ReserveTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReserveTicket)
{
    ui->setupUi(this);
    ui->seatButtonGroup->connect(ui->seatButtonGroup,
                                 SIGNAL(buttonClicked(QAbstractButton*)),
                                 this, SLOT(seatButtonClicked(QAbstractButton*)));
}

ReserveTicket::~ReserveTicket()
{
    delete ui;
}

void ReserveTicket::showError(QString error) {
    QMessageBox er;
    er.warning(this, "Seat selection", error);
}

void ReserveTicket::seatButtonClicked(QAbstractButton* b) {
    qDebug() << b->text();

    // prevent adding more than four seats
    if (selectedSeats.size() == 4) {
        qDebug() << "cannot add more than 4 seats";
        showError("You cannot select more than 4 seats");
        return;
    }

    // make the selected seats bold
    QFont font = b->font();
    font.setBold(true);
    b->setFont(font);

    // store and show selected seat info in UI
    QString seats;
    selectedSeats.append(b);

    for (int i = 0; i < selectedSeats.size(); i++) {
        seats += selectedSeats.at(i)->text();
        seats += " ";
    }

    ui->label_selectedSeats->setText(seats);
}

void ReserveTicket::on_pushButton_reset_clicked()
{

    // reset the button states
    while (! selectedSeats.empty()) {
        QAbstractButton* b = selectedSeats.first();
        QFont font = b->font();
        font.setBold(false);
        b->setFont(font);
        selectedSeats.pop_front();
    }

    ui->label_selectedSeats->setText("None");
}
