#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    QString path = QFileDialog::getOpenFileName(this,
        tr("Open RAM Dump"), "", tr("Animal Crossing RAM Dump (*.bin);;All files (*.*)"));

    if(path.length() == 0)
        exit(1);

    SaveData *saveData = SaveData::getInstance();

    if(saveData->open(path)) {

        ui->setupUi(this);

        QActionGroup *residentsMenuGroup = new QActionGroup(this);
        ui->actionResident_1->setActionGroup(residentsMenuGroup);
        ui->actionResident_2->setActionGroup(residentsMenuGroup);
        ui->actionResident_3->setActionGroup(residentsMenuGroup);
        ui->actionResident_4->setActionGroup(residentsMenuGroup);

        QString name = saveData->readString(OFFSET_PLAYER1_NAME, 8);
        uint abd = saveData->readInt32(OFFSET_PLAYER1_ABD);
        uint wallet = saveData->readInt32(OFFSET_PLAYER1_WALLET);

        ui->residentBox->setTitle(name);
        ui->residentABDLabel->setText(QString::number(abd) + " " + tr("Bells"));
        ui->residentWalletLabel->setText(QString::number(wallet) + " " + tr("Bells"));

    } else {
        exit(1);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{
    QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Save"),
                          tr("Are you sure you want to save?"), QMessageBox::Yes | QMessageBox::No);

    if(answer == QMessageBox::Yes) {
        if(SaveData::getInstance()->save())
            QMessageBox::information(this, tr("Saved"), tr("Your data has been saved!"), QMessageBox::Ok);
        else
            QMessageBox::warning(this, tr("Error"),
                                 tr("Unable to save! Make sure your save file is not being used by another process!"),
                                 QMessageBox::Ok);
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("Game-Hackers.com"));
}

void MainWindow::on_residentSetABD_clicked()
{
    SaveData *saveData = SaveData::getInstance();
    uint current = saveData->readInt32(OFFSET_PLAYER1_ABD);
    uint value = QInputDialog::getInt(this, tr("Set ABD"), tr("Enter a value for your ABD: "), current, 0, 999999999);

    saveData->writeInt32(OFFSET_PLAYER1_ABD, value);
    ui->residentABDLabel->setText(QString::number(value) + " " + tr("Bells"));
}

void MainWindow::on_residentSetWallet_clicked()
{
    SaveData *saveData = SaveData::getInstance();
    uint current = saveData->readInt32(OFFSET_PLAYER1_WALLET);
    uint value = QInputDialog::getInt(this, tr("Set Wallet"), tr("Enter a value for your wallet: "), current, 0, 999999);

    saveData->writeInt32(OFFSET_PLAYER1_WALLET, value);
    ui->residentWalletLabel->setText(QString::number(value) + " " + tr("Bells"));
}

