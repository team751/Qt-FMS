#include "dspacketmaker.h"
#include <boost/crc.hpp>

const int DSPacketMaker::PACKET_SIZE = 74;

DSPacketMaker::DSPacketMaker() :
    packetNumber1(0),
    packetNumber2(0)
{
}

QByteArray DSPacketMaker::buildPacket(FMSDefs::RobotState robotState, FMSDefs::AllianceColor allianceColor, FMSDefs::DriverStationNumber station) {
    
    //Create a 74-byte-long packet with each value initialized to zero
    QByteArray packet(PACKET_SIZE, 0);
    
    //Packet number
    packet[0] = packetNumber1;
    packet[1] = packetNumber2;
    
    //Robot state
    packet[2] = robotState;
    
    packet[3] = allianceColor;
    packet[4] = station;
    
    // FMS version
    packet[18] = 0;
    packet[19] = 6;
    packet[20] = 2;
    packet[21] = 5;
    packet[22] = 0;
    packet[23] = 8;
    packet[24] = 4;
    packet[25] = 6;
    
    //CRC-32 checksum
    boost::crc_32_type crcCalc;
    crcCalc.process_bytes(packet.constData(), packet.size());
    qint32 crc32 = crcCalc.checksum();
    //Split the 32 bits (4 bytes) into 4 individual bytes
    //I don't really understand this
    packet[70] = (crc32 >> 24);
    packet[71] = (crc32 >> 16) & 0xFF;
    packet[72] = (crc32 >> 8) & 0xFF;
    packet[73] = crc32 & 0xFF;
    
    updatePacketNumbers();
    
    return packet;
}

void DSPacketMaker::updatePacketNumbers() {
    
    if(packetNumber2 == 0) {
        //In first phase, incrementing first number
        
        if(packetNumber1 == 0xFF) {
            //Time to roll over
            packetNumber1 = 0x0;
            packetNumber2++;
        }
        else {
            //increment number 1
            packetNumber1++;
        }
    }
    else {
        //In second phase, incrementing second number
        
        if(packetNumber2 == 0xFF) {
            //Time to roll everything back to zero
            packetNumber1 = 0x0;
            packetNumber2 = 0x0;
        }
        else {
            //Increment number 2
            packetNumber2++;
        }
    }
}
