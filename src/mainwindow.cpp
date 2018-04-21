#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbusdialog.h"
#include "addlocationdialog.h"
#include <QDebug>
#include "database.h"
#include <string>
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

// Initiate the available buses based on user ticket choice (under Reservation tab)
void MainWindow::setBusList() {
    QStringList labels;
    ui->busList->setRowCount(1);
    ui->busList->setColumnCount(2);

    labels << tr("Bus Name") << tr("Seats Available");
    ui->busList->setHorizontalHeaderLabels(labels);

    // test data, actual function will be completed later
    ui->busList->setItem(0, 0, new QTableWidgetItem("VIP"));
    ui->busList->setItem(0, 1, new QTableWidgetItem("27"));

    ui->busList->setRowCount(2);
    ui->busList->setItem(1, 0, new QTableWidgetItem("Anabil"));
    ui->busList->setItem(1, 1, new QTableWidgetItem("25"));
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

// Signal slot for the "busList" table
void MainWindow::on_busList_cellDoubleClicked(int row, int column)
{
    qDebug() << row << " " << column << " clicked";
    qDebug() << ui->busList->item(row, 0)->text();
    qDebug() << ui->busList->item(row, 1)->text();
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
