#ifndef DSSENDER_H
#define DSSENDER_H

#include <QObject>
#include <QUdpSocket>

#include "dspacketmaker.h"
#include "FMSDefs.h"

/**
 * @brief The DSSender class sends packets to a driver station
 */
class DSSender : public QObject
{
    Q_OBJECT
public:
    
    /**
     * @brief DSSender
     * @param color The alliance color for this sender
     * @param number The driver station number for this sender
     * @param parent
     */
    DSSender(FMSDefs::AllianceColor color, FMSDefs::DriverStationNumber number, QObject *parent = 0);
    
protected:
    
    void timerEvent(QTimerEvent *);
    
private:
    /**
     * @brief PORT The UDP port number over which packets are sent
     */
    static const quint16 PORT;
    
    /**
     * @brief teamNumber The number of the team to send status information to
     */
    quint16 teamNumber;
    
    /**
     * @brief driverStationAddress The IP address of the team's driver station computer
     */
    QHostAddress driverStationAddress;
    
    /**
     * @brief udpSocket The socket used to send packets
     */
    QUdpSocket udpSocket;
    
    /**
     * @brief packetMaker assembles packets
     */
    DSPacketMaker packetMaker;
    
    /**
     * @brief color The alliance color of this driver station
     */
    FMSDefs::AllianceColor color;
    /**
     * @brief number The number of this driver station
     */
    FMSDefs::DriverStationNumber number;
    /**
     * @brief state The current robot state
     */
    FMSDefs::RobotState state;
    
signals:
    
public slots:
    
    /**
     * @brief setTeamNumber Set the team number to send data to
     * @param newTeamNumber
     */
    void setTeamNumber(quint16 newTeamNumber);
    
    /**
     * @brief setState changes the state. This immediately sends a packet
     * to the driver station indicating that the state has changed.
     * @param newState
     */
    void setState(FMSDefs::RobotState newState);
    
    void autonomousStarted();
    
    void autonomousFinished();
    
    void teleopStarted();
    
    void teleopFinished();
    
    void matchFinished();
    
    /**
     * @brief sendPacket sends a packet to the driver station
     */
    void sendPacket();
    
};

#endif // DSSENDER_H
