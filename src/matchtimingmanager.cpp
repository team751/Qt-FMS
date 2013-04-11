#include "matchtimingmanager.h"
#include <QDebug>

//constants
const double MatchTimingManager::autonomousTime = 15;

const double MatchTimingManager::teleopTime = 120;

MatchTimingManager::MatchTimingManager(QObject *parent) :
    QObject(parent),
    matchTimerId(0),
    phase(BetweenMatches)
{
}

void MatchTimingManager::startMatch() {
    
    phase = Autonomous;
    
    //Start a timer, running every ? milliseconds
    matchTimerId = startTimer(10);
    elapsedTimer.start();
    
    qDebug() << "Match staring";
    
    emit matchStarted();
    emit autonomousStarted();
}

void MatchTimingManager::abortMatch() {
    
    if(phase == Autonomous) {
        emit autonomousFinished();
    }
    else if(phase == Teleop) {
        emit teleopFinished();
    }
    
    emit matchFinished();
    
    phase = BetweenMatches;
    if(matchTimerId) {
        killTimer(matchTimerId);
    }
    
    qDebug() << "Match aborted";
}

void MatchTimingManager::timerEvent(QTimerEvent *) {
    
    qint64 elapsedTime = elapsedTimer.elapsed();
    
    switch(phase) {
    
    case BetweenMatches:
        
        break;
        
    case Autonomous:
        
        if(elapsedTime > autonomousTime * 1000) {
            doTeleopStart();
        }
        
        break;
        
    case Teleop:
        
        if(elapsedTime > (autonomousTime * 1000 + teleopTime * 1000)) {
            doMatchEnd();
        }
        
        break;
    
    default:
        break;
    }
    
    emit timeChanged(elapsedTime);
}

void MatchTimingManager::doTeleopStart() {
    phase = Teleop;
    
    qDebug() << "Teleop starting";
    
    emit autonomousFinished();
    emit teleopStarted();
}

void MatchTimingManager::doMatchEnd() {
    
    qDebug() << "Match finished";
    
    phase = BetweenMatches;
    killTimer(matchTimerId);
    matchTimerId = 0;
    elapsedTimer.invalidate();
    emit teleopFinished();
    emit matchFinished();
}
