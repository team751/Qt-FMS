#include "dssender.h"
#include <QDebug>

const quint16 DSSender::PORT = 1120;

DSSender::DSSender(FMSDefs::AllianceColor color, FMSDefs::DriverStationNumber number, QObject *parent) :
    QObject(parent),
    teamNumber(0),
    color(color),
    number(number),
    state(FMSDefs::AutonomousDisabled)
{
    setTeamNumber(1);
    
    //Start the timer to send a packet every x milliseconds
    startTimer(300);
}

void DSSender::setTeamNumber(quint16 newTeamNumber) {
    if(newTeamNumber != teamNumber) {
        teamNumber = newTeamNumber;
        //Update the address
        bool success = driverStationAddress.setAddress("10." + QString::number(teamNumber / 100) + '.' + QString::number(teamNumber % 100) + ".5");
        
        Q_ASSERT(success);
    }
}

void DSSender::timerEvent(QTimerEvent *) {
    sendPacket();
}

void DSSender::sendPacket() {
    QByteArray packet = packetMaker.buildPacket(state, color, number);
    
    qint64 writeCount = udpSocket.writeDatagram(packet, driverStationAddress, PORT);
    if(writeCount < 1) {
//        qWarning() << "Failed to send to" << driverStationAddress << "!" << udpSocket.errorString() << udpSocket.error();
    }
}

void DSSender::setState(FMSDefs::RobotState newState) {
    if(state != newState) {
        state = newState;
        sendPacket();
    }
}

void DSSender::autonomousStarted() {
    setState(FMSDefs::AutonomousEnabled);
}

void DSSender::autonomousFinished() {
    setState(FMSDefs::AutonomousDisabled);
}

void DSSender::teleopStarted() {
    setState(FMSDefs::TeleopEnabled);
}

void DSSender::teleopFinished() {
    setState(FMSDefs::TeleopDisabled);
}

void DSSender::matchFinished() {
    //Set to autonomous disabled, in preparation for another match
    setState(FMSDefs::AutonomousDisabled);
}
