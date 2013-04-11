#include "teamstation.h"

TeamStation::TeamStation(FMSDefs::AllianceColor color, FMSDefs::DriverStationNumber number, QObject *parent) :
    QObject(parent),
    sender(color, number),
    lastData(new DSData())
{
    //Mark the timer as invalidated to denote that data has not yet
    //been received
    dataTimer.invalidate();
}

void TeamStation::newData(std::auto_ptr<DSData> newData) {
    
    lastData = newData;
    
    dataTimer.start();
}

bool TeamStation::isDriverStationConnected() {
    //Return false if no data has been received
    if(!dataTimer.isValid()) {
        return false;
    }
    
    //Return true if the last packet arrived <200ms ago.
    //They are expected to arrive every 100ms.
    if(dataTimer.elapsed() < 200) {
        return true;
    }
    
    return false;
}

quint16 TeamStation::getMissedPacketCount() {
    return lastData->missedPacketCount;
}

quint16 TeamStation::getTripTime() {
    return lastData->tripTime;
}

double TeamStation::getRobotBatteryVoltage() {
    return lastData->batteryVoltage;
}

//Delegate slots
void TeamStation::setTeamNumber(quint16 newTeamNumber) {
    sender.setTeamNumber(newTeamNumber);
}
void TeamStation::autonomousStarted() {
    sender.autonomousStarted();
}
void TeamStation::autonomousFinished() {
    sender.autonomousFinished();
}
void TeamStation::teleopStarted() {
    sender.teleopStarted();
}
void TeamStation::teleopFinished() {
    sender.teleopFinished();
}
void TeamStation::matchFinished() {
    sender.matchFinished();
}
