#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setBusList();
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
    ui->busList->setItem(0, 0, new QTableWidgetItem("VIP"));
    ui->busList->setItem(0, 1, new QTableWidgetItem("27"));
}

// Signal slot for the "busList" table
void MainWindow::on_busList_cellDoubleClicked(int row, int column)
{
    qDebug() << row << " " << column << " clicked";
    qDebug() << ui->busList->item(0, 0)->text();
    qDebug() << ui->busList->item(0, 1)->text();
}
