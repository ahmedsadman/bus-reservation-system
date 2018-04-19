#include "addbusdialog.h"
#include "ui_addbusdialog.h"
#include "database.h"
#include <QMessageBox>

AddBusDialog::AddBusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBusDialog)
{
    ui->setupUi(this);
    Database *db = Database::getInstance();
    ui->combo_origin->insertItems(0, db->locations);
    ui->combo_dest->insertItems(0, db->locations);
    ui->combo_bustype->insertItems(0, db->bus_types);
}

void AddBusDialog::showError(QString error) {
    QMessageBox er;
    er.critical(this, "Error", error);
}

bool AddBusDialog::validate() {
    if (getName() == "") {
        showError("Please enter a bus name");
        return false;
    }

    if (getOrigin() == getDest()) {
        showError("Origin and destination cannot be same");
        return false;
    }

    return true;
}

AddBusDialog::~AddBusDialog()
{
    delete ui;
}

void AddBusDialog::on_button_save_clicked()
{
    if (validate()) {
        Database *db = Database::getInstance();
        db->insertBus(getName(), getOrigin(), getDest(), getType());
        AddBusDialog::accept();
    }
}

QString AddBusDialog::getName() {
    return ui->edit_busname->text();
}

QString AddBusDialog::getOrigin() {
    return ui->combo_origin->currentText();
}

QString AddBusDialog::getDest() {
    return ui->combo_dest->currentText();
}

QString AddBusDialog::getType() {
    return ui->combo_bustype->currentText();
}
