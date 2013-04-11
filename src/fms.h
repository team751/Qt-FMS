#ifndef FMS_H
#define FMS_H

#include <QObject>

#include "teamstation.h"
#include "matchtimingmanager.h"

/**
 * @brief The FMS class manages match timing and driver station communication
 */
class FMS : public QObject
{
    Q_OBJECT
public:
    explicit FMS(QObject *parent = 0);
    
    /**
     * @brief Returns true if a match is in progress, otherwise returns false
     */
    bool isInMatch();
    
protected:
    
    void timerEvent(QTimerEvent *);
    
private:
    
    MatchTimingManager timing;
    
    DSReceiver receiver;
    
    TeamStation red1;
    TeamStation red2;
    TeamStation red3;
    
    TeamStation blue1;
    TeamStation blue2;
    TeamStation blue3;
    
signals:
    
    /**
     * @brief Emitted frequently when the time changes during a match
     * @param millisecondsElapsed The number of milliseconds that have passed
     * since the match started
     */
    void timeChanged(quint64 millisecondsElapsed);
    
public slots:
    
    void setRed1Team(quint16 team);
    void setRed2Team(quint16 team);
    void setRed3Team(quint16 team);
    
    void setBlue1Team(quint16 team);
    void setBlue2Team(quint16 team);
    void setBlue3Team(quint16 team);
    
    void startMatch();
    
    void abortMatch();
    
};

#endif // FMS_H
