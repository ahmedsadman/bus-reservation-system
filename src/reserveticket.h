#ifndef RESERVETICKET_H
#define RESERVETICKET_H

#include <QDialog>

namespace Ui {
class ReserveTicket;
}

class ReserveTicket : public QDialog
{
    Q_OBJECT

public:
    explicit ReserveTicket(QWidget *parent = 0);
    ~ReserveTicket();

private:
    Ui::ReserveTicket *ui;
};

#endif // RESERVETICKET_H
