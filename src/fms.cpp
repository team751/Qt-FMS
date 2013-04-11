#include "fms.h"

FMS::FMS(QObject *parent) :
    QObject(parent),
    red1(FMSDefs::RedAlliance, FMSDefs::Station1),
    red2(FMSDefs::RedAlliance, FMSDefs::Station2),
    red3(FMSDefs::RedAlliance, FMSDefs::Station3),
    blue1(FMSDefs::BlueAlliance, FMSDefs::Station1),
    blue2(FMSDefs::BlueAlliance, FMSDefs::Station3),
    blue3(FMSDefs::BlueAlliance, FMSDefs::Station3)
{
    //Set default team numbers
    red1.setTeamNumber(751);
    red2.setTeamNumber(111);
    red3.setTeamNumber(254);
    blue1.setTeamNumber(696);
    blue2.setTeamNumber(1280);
    blue3.setTeamNumber(971);
    
    //Connect things
    
    connect(&timing, &MatchTimingManager::timeChanged, this, &FMS::timeChanged);
    
    //Match timing
    connect(&timing, &MatchTimingManager::autonomousStarted, &red1, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &red1, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &red1, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &red1, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &red1, &TeamStation::matchFinished);
    
    connect(&timing, &MatchTimingManager::autonomousStarted, &red2, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &red2, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &red2, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &red2, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &red2, &TeamStation::matchFinished);
    
    connect(&timing, &MatchTimingManager::autonomousStarted, &red3, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &red3, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &red3, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &red3, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &red3, &TeamStation::matchFinished);
    
    connect(&timing, &MatchTimingManager::autonomousStarted, &blue1, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &blue1, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &blue1, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &blue1, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &blue1, &TeamStation::matchFinished);
    
    connect(&timing, &MatchTimingManager::autonomousStarted, &blue2, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &blue2, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &blue2, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &blue2, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &blue2, &TeamStation::matchFinished);
    
    connect(&timing, &MatchTimingManager::autonomousStarted, &blue3, &TeamStation::autonomousStarted);
    connect(&timing, &MatchTimingManager::autonomousFinished, &blue3, &TeamStation::autonomousFinished);
    connect(&timing, &MatchTimingManager::teleopStarted, &blue3, &TeamStation::teleopStarted);
    connect(&timing, &MatchTimingManager::teleopFinished, &blue3, &TeamStation::teleopFinished);
    connect(&timing, &MatchTimingManager::matchFinished, &blue3, &TeamStation::matchFinished);
}

void FMS::timerEvent(QTimerEvent *) {
    
}

void FMS::setRed1Team(quint16 team) {
    red1.setTeamNumber(team);
}
void FMS::setRed2Team(quint16 team) {
    red2.setTeamNumber(team);
}
void FMS::setRed3Team(quint16 team) {
    red3.setTeamNumber(team);
}
void FMS::setBlue1Team(quint16 team) {
    blue1.setTeamNumber(team);
}
void FMS::setBlue2Team(quint16 team) {
    blue2.setTeamNumber(team);
}
void FMS::setBlue3Team(quint16 team) {
    blue2.setTeamNumber(team);
}

void FMS::startMatch() {
    timing.startMatch();
}

void FMS::abortMatch() {
    timing.abortMatch();
}

bool FMS::isInMatch() {
    return timing.isInMatch();
}
