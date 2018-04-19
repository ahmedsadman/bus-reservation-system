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

// Initiate the busList based on user data
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
        qDebug() << ab.getName();
        qDebug() << ab.getOrigin();
        qDebug() << ab.getDest();
        qDebug() << ab.getType();
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


// remove location record on button click
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
