#ifndef DSPACKETMAKER_H
#define DSPACKETMAKER_H

#include <QByteArray>

#include "FMSDefs.h"

/**
 * @brief The DSPacketMaker class assembles data packets to send to a driver station.
 * It keeps track of packet numbers.
 */
class DSPacketMaker
{
public:
    DSPacketMaker();
    
    /**
     * @brief kPacketSize The size of a packet, in bytes
     */
    static const int PACKET_SIZE;
    
    
    /**
     * @brief buildPacket Assembles a packet to send
     * @param robotState
     * @param allianceColor
     * @param station
     * @return 
     */
    QByteArray buildPacket(FMSDefs::RobotState robotState, FMSDefs::AllianceColor allianceColor, FMSDefs::DriverStationNumber station);
    
private:
    
    /**
     * @brief packetNumber1 The first packet number. This increments from 0 to 255. After 255,
     * it rolls over to zero and packetNumber2 starts incrementing.
     */
    quint8 packetNumber1;
    
    /**
     * @brief packetNumber2 The second packet number. After packetNumber1 rolls over from 255 to zero,
     * this packet number starts incrementing. When this reaches 255, it rolls over to zero and
     * cycle begins again.
     */
    quint8 packetNumber2;
    
    
    /**
     * @brief updatePacketNumbers Increment the packet numbers as necessary. This should be called after assembling each packet.
     */
    void updatePacketNumbers();
    
};

#endif // DSPACKETMAKER_H
