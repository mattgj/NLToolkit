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

        // Connect the residents to the same slot.
        foreach (QAction *resident, ui->menuResident->actions())
            this->connect(resident, SIGNAL(triggered()),
                          this, SLOT(on_actionResident_triggered()));

        // Retrieve the mayor's information initially.
        QString name = saveData->readString(OFFSET_PLAYER_NAME, 8);
        uint abd = saveData->readInt32(OFFSET_PLAYER_ABD);
        uint wallet = saveData->readInt32(OFFSET_PLAYER_WALLET);

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

quint8 MainWindow::getPlayerID() const
{
    for (quint8 i = 0; i < ui->menuResident->actions().length(); ++i)
        if (ui->menuResident->actions().at(i)->isChecked())
            return i;
    return 0;
}

quint32 MainWindow::getPlayerNameOffset() const
{
    return OFFSET_PLAYER_NAME + (this->getPlayerID() * OFFSET_PLAYER_OFFSET);
}

quint32 MainWindow::getPlayerWalletOffset() const
{
    return OFFSET_PLAYER_WALLET + (this->getPlayerID() * OFFSET_PLAYER_OFFSET);
}

quint32 MainWindow::getPlayerABDOffset() const
{
    return OFFSET_PLAYER_ABD + (this->getPlayerID() * OFFSET_PLAYER_OFFSET);
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
    uint current = saveData->readInt32(this->getPlayerABDOffset());
    uint value = QInputDialog::getInt(this, tr("Set ABD"), tr("Enter a value for your ABD: "), current, 0, 999999999);

    saveData->writeInt32(this->getPlayerABDOffset(), value);
    ui->residentABDLabel->setText(QString::number(value) + " " + tr("Bells"));
}

void MainWindow::on_residentSetWallet_clicked()
{
    SaveData *saveData = SaveData::getInstance();
    uint current = saveData->readInt32(this->getPlayerWalletOffset());
    uint value = QInputDialog::getInt(this, tr("Set Wallet"), tr("Enter a value for your wallet: "), current, 0, 999999);

    saveData->writeInt32(this->getPlayerWalletOffset(), value);
    ui->residentWalletLabel->setText(QString::number(value) + " " + tr("Bells"));
}

void MainWindow::on_actionResident_triggered()
{
    SaveData *saveData = SaveData::getInstance();

    // Initialization
    QString name = saveData->readString(this->getPlayerNameOffset(), 8);
    uint abd = saveData->readInt32(this->getPlayerABDOffset());
    uint wallet = saveData->readInt32(this->getPlayerWalletOffset());

    // Display the proper information.
    ui->residentBox->setTitle(name);
    ui->residentABDLabel->setText(QString::number(abd) + " " + tr("Bells"));
    ui->residentWalletLabel->setText(QString::number(wallet) + " " + tr("Bells"));
}
