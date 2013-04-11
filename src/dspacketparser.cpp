#include "dspacketparser.h"
#include <QDebug>

DSPacketParser::DSPacketParser()
{
}

std::auto_ptr<DSData> DSPacketParser::parsePacket(QByteArray& packet) {
    std::auto_ptr<DSData> data(new DSData());
    
    data->robotState = parseRobotState(packet[2]);
    
    data->teamNumber = parseTeamNumber(packet[4], packet[5]);
    
    data->robotAddress = parseRobotAddress(packet[6], packet[7], packet[8], packet[9]);
    
    data->alliance = parseAllianceColor(packet[10]);
    
    data->stationNumber = parseDriverStationNumber(packet[11]);
    
    data->robotMacAddress = parseMacAddress(packet[12], packet[13], packet[14], packet[15], packet[16], packet[17]);
    
    data->driverStationVersion = parseDriverStationVersion(packet[18], packet[19], packet[20], packet[21], packet[22], packet[23], packet[24], packet[25]);
    
    data->missedPacketCount = parse16BitInt(packet[26], packet[27]);
    
    data->packetCount = parse16BitInt(packet[28], packet[29]);
    
    data->tripTime = parse16BitInt(packet[30], packet[31]);
    
    //Battery voltage: figure this out
    qDebug() << "Battery voltage values" << (int) packet[42] << (int) packet[43];
    
    return data;
}

FMSDefs::RobotState DSPacketParser::parseRobotState(const int robotState) {
    switch(robotState) {
    
    case 0x53:
        return FMSDefs::AutonomousDisabled;
        
    case 0x53 + 0x20:
        return FMSDefs::AutonomousEnabled;
        
    case 0x51:
        return FMSDefs::AutonomousNoCommunication;
        
    case 0x43:
        return FMSDefs::TeleopDisabled;
        
    case 0x43 + 0x20:
        return FMSDefs::TeleopEnabled;
        
    case 0x41:
        return FMSDefs::TeleopNoCommunication;
    
    default:
        qWarning() << "Unknown robot state" << QString::number(robotState, 16);
        return FMSDefs::AutonomousNoCommunication;
    }
}

quint16 DSPacketParser::parseTeamNumber(const int part1, const int part2) {
    return part1 * 100 + part2;
}

QHostAddress DSPacketParser::parseRobotAddress(const int part1, const int part2, const int part3, const int part4) {
    return QHostAddress( QString::number(part1) + '.' + QString::number(part2) + '.' + QString::number(part3) + '.' + QString::number(part4) );
}

FMSDefs::AllianceColor DSPacketParser::parseAllianceColor(int allianceColor) {
    switch(allianceColor) {
    
    case 0x52:
        return FMSDefs::RedAlliance;
        
    case 0x42:
        return FMSDefs::BlueAlliance;
    
    default:
        qWarning() << "Unknown alliance color" << allianceColor;
        return FMSDefs::RedAlliance;
    }
}

FMSDefs::DriverStationNumber DSPacketParser::parseDriverStationNumber(int stationNumber) {
    switch(stationNumber) {
    
    case 0x31:
        return FMSDefs::Station1;
        
    case 0x32:
        return FMSDefs::Station2;
        
    case 0x33:
        return FMSDefs::Station3;
    
    default:
        qWarning() << "Unknown driver station number" << stationNumber;
        return FMSDefs::Station1;
    }
}

QByteArray DSPacketParser::parseMacAddress(int part1, int part2, int part3, int part4, int part5, int part6) {
    return QByteArray::number(part1, 16)
            + ':' + QByteArray::number(part2, 16)
            + ':' + QByteArray::number(part3, 16)
            + ':' + QByteArray::number(part4, 16)
            + ':' + QByteArray::number(part5, 16)
            + ':' + QByteArray::number(part6, 16);
}

QString DSPacketParser::parseDriverStationVersion(char part1, char part2, char part3, char part4, char part5, char part6, char part7, char part8) {
    QString version;
    version.resize(8);
    version[0] = part1;
    version[1] = part2;
    version[2] = part3;
    version[3] = part4;
    version[4] = part5;
    version[5] = part6;
    version[6] = part7;
    version[7] = part8;
    
    return version;
}

quint16 DSPacketParser::parse16BitInt(char part1, char part2) {
    return (part1 << 8) | (part2 & 0xFF);
}
