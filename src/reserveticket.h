#ifndef REVERSETICKET_H
#define REVERSETICKET_H

#include <QDialog>

namespace Ui {
class ReverseTicket;
}

class ReverseTicket : public QDialog
{
    Q_OBJECT

public:
    explicit ReverseTicket(QWidget *parent = 0);
    ~ReverseTicket();

private:
    Ui::ReverseTicket *ui;
};

#endif // REVERSETICKET_H
