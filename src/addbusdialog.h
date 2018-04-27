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
    explicit AddBusDialog(QWidget *parent = 0, bool _dis = false);
    ~AddBusDialog();
    QString getName();
    QString getType();
    QString getOrigin();
    QString getDest();
    void setBusValues(QString busname, QString origin, QString dest, QString type);
    bool disabled_name;

private slots:
    void on_button_save_clicked();

private:
    Ui::AddBusDialog *ui;
    void showError(QString error);
    bool validate();
};

#endif // ADDBUSDIALOG_H
