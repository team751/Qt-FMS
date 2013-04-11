#include "statuswindow.h"
#include "ui_statuswindow.h"

#include "dssender.h"
#include <QDebug>

StatusWindow::StatusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatusWindow)
{
    ui->setupUi(this);
    
    connect(&fms, &FMS::timeChanged, this, &StatusWindow::updateTiming);
    
    //Maximum value is the maximum number of seconds in a match
    ui->matchProgressBar->setMaximum(qRound(MatchTimingManager::autonomousTime + MatchTimingManager::teleopTime));
    ui->matchProgressBar->setValue(0);
    
    fms.setBlue1Team(751);
}

StatusWindow::~StatusWindow()
{
    delete ui;
}

void StatusWindow::on_startMatchButton_clicked()
{
    fms.startMatch();
    ui->abortMatchButton->setEnabled(true);
    ui->startMatchButton->setEnabled(false);
}

void StatusWindow::on_abortMatchButton_clicked()
{
    fms.abortMatch();
    ui->abortMatchButton->setEnabled(false);
    ui->startMatchButton->setEnabled(true);
}

void StatusWindow::updateTiming(qint64 millisecondsElapsed) {
    int seconds = millisecondsElapsed / 1000;
    ui->matchProgressBar->setValue(seconds);
    ui->timeLabel->setText(QString::number(seconds));
}
