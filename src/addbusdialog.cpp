#include "addbusdialog.h"
#include "ui_addbusdialog.h"
#include "database.h"
#include <QMessageBox>
#include <QDebug>

AddBusDialog::AddBusDialog(QWidget *parent, bool _dis) :
    QDialog(parent),
    ui(new Ui::AddBusDialog)
{
    ui->setupUi(this);
    disabled_name = _dis;
    ui->edit_busname->setDisabled(disabled_name);
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
        (!disabled_name) ? db->insertBus(getName(), getOrigin(), getDest(), getType()) \
                         : db->editBus(getName(), getOrigin(), getDest(), getType());
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

void AddBusDialog::setBusValues(QString busname, QString origin, QString dest, QString type) {
    ui->edit_busname->setText(busname);
    qDebug() << busname << origin << dest;
    ui->combo_origin->setCurrentIndex(ui->combo_dest->findText(origin));
    ui->combo_dest->setCurrentIndex(ui->combo_dest->findText(dest));
    ui->combo_bustype->setCurrentIndex(ui->combo_bustype->findText(type));
}
