#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QActionGroup>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "savedata.h"
#include "offsets.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    quint8 getPlayerID() const;
    quint32 getPlayerNameOffset() const;
    quint32 getPlayerWalletOffset() const;
    quint32 getPlayerABDOffset() const;

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_residentSetABD_clicked();

    void on_residentSetWallet_clicked();

    void on_actionSave_triggered();

    void on_actionResident_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
