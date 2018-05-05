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
    QList<QString> getSelectedSeats();
    QString getPassengerName();
    QString getGender();
    QString getPhoneNo();


private slots:
    void seatButtonClicked(QAbstractButton* b);

    void on_pushButton_reset_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::ReserveTicket *ui;
    QList<QAbstractButton*> selectedSeats;
    void showError(QString error);
    bool validate();
};

#endif // RESERVETICKET_H
