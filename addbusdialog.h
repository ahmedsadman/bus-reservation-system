#ifndef ADDBUSDIALOG_H
#define ADDBUSDIALOG_H

#include <QDialog>

namespace Ui {
class AddBusDialog;
}

class AddBusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBusDialog(QWidget *parent = 0);
    ~AddBusDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::AddBusDialog *ui;
};

#endif // ADDBUSDIALOG_H
