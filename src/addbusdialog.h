#ifndef ADDBUSDIALOG_H
#define ADDBUSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddBusDialog;
}

class AddBusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBusDialog(QWidget *parent = 0);
    ~AddBusDialog();
    QString getName();
    QString getType();
    QString getOrigin();
    QString getDest();

private slots:
    void on_button_save_clicked();

private:
    Ui::AddBusDialog *ui;
    void showError(QString error);
    bool validate();
};

#endif // ADDBUSDIALOG_H
