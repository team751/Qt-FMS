#include "dsreceiver.h"
#include <QDebug>

DSReceiver::DSReceiver(QObject *parent) :
    QObject(parent)
{
    
    connect(&udpSocket, &QUdpSocket::readyRead, this, &DSReceiver::readDatagrams);
    
    //Bind to the port, to start receiving packets
    bool success = udpSocket.bind(1160);
    
    if(!success) {
        qWarning() << "Failed to bind" << udpSocket.error() << udpSocket.errorString();
    }
}

void DSReceiver::readDatagrams() {
    while(udpSocket.hasPendingDatagrams()) {
        QByteArray packet;
        packet.resize(udpSocket.pendingDatagramSize());
        
        QHostAddress sender;
        quint16 senderPort;
        
        udpSocket.readDatagram(packet.data(), packet.size(), &sender, &senderPort);
        
        std::auto_ptr<DSData> data = parser.parsePacket(packet);
        
        if(data->alliance == FMSDefs::RedAlliance) {
            if(data->stationNumber == FMSDefs::Station1) {
                emit newRed1Data(data);
                //Move on to the next packet
                continue;
            }
            else if(data->stationNumber == FMSDefs::Station2) {
                emit newRed2Data(data);
                continue;
            }
            else if(data->stationNumber == FMSDefs::Station3) {
                emit newRed3Data(data);
                continue;
            }
        }
        else if(data->alliance == FMSDefs::BlueAlliance) {
            if(data->stationNumber == FMSDefs::Station1) {
                emit newBlue1Data(data);
                continue;
            }
            else if(data->stationNumber == FMSDefs::Station2) {
                emit newBlue2Data(data);
                continue;
            }
            else if(data->stationNumber == FMSDefs::Station3) {
                emit newBlue3Data(data);
                continue;
            }
        }
        //This point should not be reached
        qWarning() << "Packet from driver station was not recognized!";
    }
}
