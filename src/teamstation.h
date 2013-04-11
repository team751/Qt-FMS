#ifndef TEAMSTATION_H
#define TEAMSTATION_H

#include <QObject>
#include "dssender.h"
#include "dsreceiver.h"
#include <QElapsedTimer>

/**
 * @brief The TeamStation class represents one driver station and the encompasses a DSSender
 * for sending out packets, as well as mechanisms for keeping track of the status of the
 * connections.
 */
class TeamStation : public QObject
{
    Q_OBJECT
public:
    explicit TeamStation(FMSDefs::AllianceColor color, FMSDefs::DriverStationNumber number, QObject *parent = 0);
    
    /**
     * @brief Returns true if the FMS is connected to the driver station,
     * otherwise returns false.
     * @return 
     */
    bool isDriverStationConnected();
    
    /**
     * @brief Get the number of dropped DS-robot packets over a recent time interval.
     * The return value is undefined if the driver station is not connected.
     * @return 
     */
    quint16 getMissedPacketCount();
    /**
     * @brief Get the trip time, in milliseconds, for DS-robot packets over a recent time
     * interval.
     * The return value is undefined if the driver station is not connected.
     * @return 
     */
    quint16 getTripTime();
    
    /**
     * @brief Get the voltage of the robot battery.
     * The return value is undefined if the driver station is not connected.
     * @return 
     */
    double getRobotBatteryVoltage();
    
private:
    
    DSSender sender;
    
    /**
     * @brief lastData The last data set that was received from the driver station
     */
    std::auto_ptr<DSData> lastData;
    
    /**
     * @brief dataTimer The timer used to keep track of the time since
     * data was last received
     */
    QElapsedTimer dataTimer;
    
signals:
    
public slots:
    
    /**
     * @brief setTeamNumber Set the team number to send data to
     * @param newTeamNumber
     */
    void setTeamNumber(quint16 newTeamNumber);
    
    /**
     * @brief newData is received when the DSReceiver instance
     * receives a packet for this station
     * @param newData the received data
     */
    void newData(std::auto_ptr<DSData> newData);
    
    void autonomousStarted();
    
    void autonomousFinished();
    
    void teleopStarted();
    
    void teleopFinished();
    
    void matchFinished();
    
    
};

#endif // TEAMSTATION_H
