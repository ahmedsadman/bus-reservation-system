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

QString AddLocationDialog::getVal() {
    return ui->lineEdit->text();
}

void AddLocationDialog::on_pushButton_clicked()
{
    AddLocationDialog::accept();
}
