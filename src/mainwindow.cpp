#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbusdialog.h"
#include "addlocationdialog.h"
#include <QDebug>
#include "database.h"
#include "reserveticket.h"
#include <string>
#include "bus.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = Database::getInstance();
    this->setBusList();
    this->setLocationList();
    this->setBusList_manage();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboType->insertItems(0, db->bus_types);
}

MainWindow::~MainWindow()
{
    db->disconnect();
    delete ui;
}

// Initiate the Locations and From/To fields with data
void MainWindow::setLocationList() {
    db->getLocations(); // populates location data

    QStringList labels;
    labels << tr("Locations");
    ui->locList_manage->setColumnCount(1);
    ui->locList_manage->setHorizontalHeaderLabels(labels);
    ui->locList_manage->clearContents();

    for (int i = 0; i < db->locations.size(); i++) {
        ui->locList_manage->setRowCount(i+1);
        ui->locList_manage->setItem(i, 0, new QTableWidgetItem(db->locations[i]));
    }

    // populate the From and To Comboboxes
    ui->comboFrom->clear();
    ui->comboFrom->insertItems(0, db->locations);
    ui->comboTo->clear();
    ui->comboTo->insertItems(0, db->locations);
}

// Initiate the trip related bus table
void MainWindow::setBusList() {
    QStringList labels;
    // ui->busList->setRowCount(1);
    ui->busList->setColumnCount(2);

    labels << tr("Bus Name") << tr("Seats Available");
    ui->busList->setHorizontalHeaderLabels(labels);
}

// get user trip info, and show available bus
void MainWindow::populateTripBus() {
    QString from = ui->comboFrom->currentText();
    QString to = ui->comboTo->currentText();
    QString type = ui->comboType->currentText();

    QList<Bus> buses = db->getBusByTripInfo(from, to, type);

    if (buses.isEmpty()) return;

    for (int i = 0; i < buses.size(); i++) {
        ui->busList->setRowCount(i+1);
        ui->busList->setItem(i, 0, new QTableWidgetItem(buses[i].getBusname()));
        ui->busList->setItem(i, 1, new QTableWidgetItem("30"));
    }
}

// populates all the bus data under Manage tab
void MainWindow::setBusList_manage() {
    db->getBuses();
    QStringList labels;
    ui->busList_manage->clearContents();
    ui->busList_manage->setColumnCount(4);
    labels << tr("Name") << tr("Origin") << tr("Destination") << tr("Type");
    ui->busList_manage->setHorizontalHeaderLabels(labels);
    qDebug() << "Populating manage bus table";

    for (int i = 0; i < db->buses.size(); i++) {
        ui->busList_manage->setRowCount(i+1);
        ui->busList_manage->setItem(i, 0, new QTableWidgetItem(db->buses[i]->getBusname()));
        ui->busList_manage->setItem(i, 1, new QTableWidgetItem(db->buses[i]->getOrigin()));
        ui->busList_manage->setItem(i, 2, new QTableWidgetItem(db->buses[i]->getDest()));
        ui->busList_manage->setItem(i, 3, new QTableWidgetItem(db->buses[i]->getType()));
    }
}

// opens the reserve ticket window
void MainWindow::on_busList_cellDoubleClicked(int row, int column)
{
    ReserveTicket rs;
    rs.setModal(true);

    if (rs.exec() == QDialog::Accepted) {

        // insert ticket data in database
        QList<QString> seat_list = rs.getSelectedSeats();
        QString pname = rs.getPassengerName();
        QString gender = rs.getGender();
        QString pno = rs.getPhoneNo();
        QString from = ui->comboFrom->currentText();
        QString to = ui->comboTo->currentText();
        QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
        QString bname = ui->busList->item(row, 0)->text();

        for (int i = 0; i < seat_list.size(); i++) {
            db->insertTicket(pname, gender, pno, bname, from, to, date, seat_list.at(i));
        }

        qDebug() << "ticket insertion complete";
    }
}


// Exit program via Menu
void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

// launch the window to add new bus
void MainWindow::on_btnAdd_bus_clicked()
{
    AddBusDialog ab;
    ab.setModal(true);

    if (ab.exec() == QDialog::Accepted) {
        this->setBusList_manage();
    }
}

// launch the window to add new locations
void MainWindow::on_btnAdd_loc_clicked()
{
    AddLocationDialog al;
    al.setModal(true);

    if (al.exec() == QDialog::Accepted) {
        db->insertLocation(al.getVal());
        this->setLocationList();
    }
}


// remove location record on button click (Manage tab)
void MainWindow::on_btnRemove_loc_clicked()
{
    QModelIndexList indexes = ui->locList_manage->selectionModel()->selection().indexes();

    if (indexes.count() > 0) {
        QModelIndex index = indexes.at(0);
        QString locname = ui->locList_manage->item(index.row(), 0)->text();
        db->removeLoc(locname); // also remove from database
        // ui->locList_manage->removeRow(index.row());
        this->setLocationList();
        qDebug() << locname;
    }

}

// remove a bus record on button click (Manage tab)
void MainWindow::on_btnRemove_bus_clicked()
{
    QModelIndexList indexes = ui->busList_manage->selectionModel()->selection().indexes();

    if (indexes.count() > 0) {
        QModelIndex index = indexes.at(0);
        QString busname = ui->busList_manage->item(index.row(), 0)->text();
        qDebug() << "removing bus " << busname;
        db->removeBus(busname);
        this->setBusList_manage();
    }
}

void MainWindow::on_btnEdit_bus_clicked()
{
    AddBusDialog ab(0, true);
    ab.setModal(true);
    QString busname, origin, dest, type;
    QModelIndexList indexes = ui->busList_manage->selectionModel()->selection().indexes();


    QModelIndex index = indexes.at(0);
    busname = ui->busList_manage->item(index.row(), 0)->text();
    origin = ui->busList_manage->item(index.row(), 1)->text();
    dest = ui->busList_manage->item(index.row(), 2)->text();
    type = ui->busList_manage->item(index.row(), 3)->text();
    ab.setBusValues(busname, origin, dest, type);

    if (ab.exec() == QDialog::Accepted)
        this->setBusList_manage();
}

// loads bus info based on user trip info
void MainWindow::on_button_load_clicked()
{
    qDebug() << "Getting bus data";
    ui->busList->clearContents();
    ui->busList->setRowCount(0);
    this->populateTripBus();
}
