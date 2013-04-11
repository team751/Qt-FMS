#ifndef DSPACKETPARSER_H
#define DSPACKETPARSER_H

#include "FMSDefs.h"
#include <QtGlobal>
#include <QHostAddress>
#include <memory>

/**
 * @brief The DSData struct contains all the data that the driver station sends
 */
struct DSData {
    
    /**
     * @brief DSData Constructor. Sets all primitive values to zero.
     */
    DSData() :
        robotState(FMSDefs::AutonomousNoCommunication),
        teamNumber(1),
        alliance(FMSDefs::RedAlliance),
        stationNumber(FMSDefs::Station1),
        missedPacketCount(0),
        packetCount(0),
        tripTime(0),
        batteryVoltage(0)
    {
        
    }
    
    FMSDefs::RobotState robotState;
    quint16 teamNumber;
    QHostAddress robotAddress;
    
    FMSDefs::AllianceColor alliance;
    FMSDefs::DriverStationNumber stationNumber;
    
    /**
     * @brief robotMACAddress Six bytes, storing the robot's MAC address
     */
    QByteArray robotMacAddress;
    
    QString driverStationVersion;
    
    /**
     * @brief missedPacketCount
     */
    quint16 missedPacketCount;
    
    /**
     * @brief packetCount The total number of packets that have been sent
     * to the robot
     */
    quint16 packetCount;
    /**
     * @brief tripTime DS-robot packet trip time, in milliseconds
     */
    quint16 tripTime;
    
    double batteryVoltage;
};

/**
 * @brief The DSPacketParser class parses packets received from driver stations
 */
class DSPacketParser
{
public:
    
    DSPacketParser();
    
    /**
     * @brief parsePacket parses a packet from a driver station and returns the data from it
     * @param packet
     * @return 
     */
    std::auto_ptr<DSData> parsePacket(QByteArray& packet);
    
private:
    
    static FMSDefs::RobotState parseRobotState(const int robotState);
    
    static quint16 parseTeamNumber(const int part1, const int part2);
    
    static QHostAddress parseRobotAddress(const int part1, const int part2, const int part3, const int part4);
    
    static FMSDefs::AllianceColor parseAllianceColor(int allianceColor);
    
    static FMSDefs::DriverStationNumber parseDriverStationNumber(int stationNumber);
    
    static QByteArray parseMacAddress(int part1, int part2, int part3, int part4, int part5, int part6);
    
    static QString parseDriverStationVersion(char part1, char part2, char part3, char part4, char part5, char part6, char part7, char part8);
    
    /**
     * @brief parse16BitInt parses two 8-bit integers into one 16-bit unsigned integer
     * @param part1 The first, most significatnt part
     * @param part2 The second, least significant part
     * @return 
     */
    static quint16 parse16BitInt(char part1, char part2);
};

#endif // DSPACKETPARSER_H
