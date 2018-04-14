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
    this->setBusList();
    Database a;

    // example of using the database
//    a.createBusTable();
//    a.createLocTable();
//    a.insertLocation("Dhaka");
//    a.disconnect();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ab.exec();
}

// launch the window to add new locations
void MainWindow::on_btnAdd_loc_clicked()
{
    AddLocationDialog al;
    al.setModal(true);
    al.exec();
}
