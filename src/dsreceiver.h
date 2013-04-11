#ifndef DSRECEIVER_H
#define DSRECEIVER_H

#include <QObject>
#include <QUdpSocket>

#include "FMSDefs.h"
#include "dspacketparser.h"

/**
 * @brief The DSReceiver class receives, parses, and sorts packets from driver stations.
 *
 * One instance of this class exists for all six driver stations.
 *
 * As soon as an instance is constructed, it will start listening for packets and emitting
 * signals when information is received.
 */
class DSReceiver : public QObject
{
    Q_OBJECT
public:
    explicit DSReceiver(QObject *parent = 0);
    
private:
    
    /**
     * @brief udpSocket The socket used to receive packets
     */
    QUdpSocket udpSocket;
    
    DSPacketParser parser;
    
signals:
    
    /**
     * @brief newRed1Data is emitted when a packet is received
     * from the red 1 driver station
     * @param newData
     */
    void newRed1Data(std::auto_ptr<DSData> newData);
    
    /**
     * @brief newRed2Data is emitted when a packet is received
     * from the red 2 driver station
     * @param newData
     */
    void newRed2Data(std::auto_ptr<DSData> newData);
    
    /**
     * @brief newRed3Data is emitted when a packet is received
     * from the red 3 driver station
     * @param newData
     */
    void newRed3Data(std::auto_ptr<DSData> newData);
    
    /**
     * @brief newBlue1Data is emitted when a packet is received
     * from the blue 1 driver station
     * @param newData
     */
    void newBlue1Data(std::auto_ptr<DSData> newData);
    
    /**
     * @brief newBlue2Data is emitted when a packet is received
     * from the blue 2 driver station
     * @param newData
     */
    void newBlue2Data(std::auto_ptr<DSData> newData);
    
    /**
     * @brief newBlue3Data is emitted when a packet is received
     * from the blue 3 driver station
     * @param newData
     */
    void newBlue3Data(std::auto_ptr<DSData> newData);
    
public slots:
    
private slots:
    
    /**
     * @brief readDatagrams gets packets from the UDP socket when they arrive
     */
    void readDatagrams();
    
};

#endif // DSRECEIVER_H
