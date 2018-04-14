#include "addbusdialog.h"
#include "ui_addbusdialog.h"

AddBusDialog::AddBusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBusDialog)
{
    ui->setupUi(this);
}

AddBusDialog::~AddBusDialog()
{
    delete ui;
}

void AddBusDialog::on_pushButton_2_clicked()
{
    AddBusDialog::accept();
}
