#ifndef RESERVETICKET_H
#define RESERVETICKET_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ReserveTicket;
}

class ReserveTicket : public QDialog
{
    Q_OBJECT

public:
    explicit ReserveTicket(QWidget *parent = 0);
    ~ReserveTicket();

private slots:
    void seatButtonClicked(QAbstractButton* b);

    void on_pushButton_reset_clicked();

private:
    Ui::ReserveTicket *ui;
    QList<QAbstractButton*> selectedSeats;
    void showError(QString error);
};

#endif // RESERVETICKET_H
