#ifndef ADDLOCATIONDIALOG_H
#define ADDLOCATIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddLocationDialog;
}

class AddLocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocationDialog(QWidget *parent = 0);
    QString getVal();
    ~AddLocationDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddLocationDialog *ui;
};

#endif // ADDLOCATIONDIALOG_H
