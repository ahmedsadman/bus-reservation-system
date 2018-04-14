#include "addlocationdialog.h"
#include "ui_addlocationdialog.h"

AddLocationDialog::AddLocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLocationDialog)
{
    ui->setupUi(this);
}

AddLocationDialog::~AddLocationDialog()
{
    delete ui;
}
