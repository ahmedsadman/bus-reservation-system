#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_busList_cellDoubleClicked(int row, int column);

    void on_actionExit_triggered();

    void on_btnAdd_bus_clicked();

    void on_btnAdd_loc_clicked();

    void on_btnRemove_loc_clicked();

    void on_btnRemove_bus_clicked();

    void on_btnEdit_bus_clicked();

    void on_button_load_clicked();

private:
    Ui::MainWindow *ui;
    Database *db;
    void MainWindow::setBusList();
    void MainWindow::populateTripBus();
    void MainWindow::setLocationList();
    void MainWindow::setBusList_manage();
};

#endif // MAINWINDOW_H
