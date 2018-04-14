#ifndef ADDLOCATIONDIALOG_H
#define ADDLOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddLocationDialog;
}

class AddLocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocationDialog(QWidget *parent = 0);
    ~AddLocationDialog();

private:
    Ui::AddLocationDialog *ui;
};

#endif // ADDLOCATIONDIALOG_H
