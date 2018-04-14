#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    void MainWindow::setBusList();
};

#endif // MAINWINDOW_H
