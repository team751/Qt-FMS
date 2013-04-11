#ifndef MATCHTIMINGMANAGER_H
#define MATCHTIMINGMANAGER_H

#include <QObject>
#include <QElapsedTimer>

/**
 * @brief The MatchTimingManager class keeps track of the timing of a match
 */
class MatchTimingManager : public QObject
{
    Q_OBJECT
public:
    
    /**
     * @brief The MatchPhase enum defines phases of a match that the system
     * can be in
     */
    enum MatchPhase {
        BetweenMatches,
        Autonomous,
        Teleop,
    };
    
    explicit MatchTimingManager(QObject *parent = 0);
    
    /**
     * @brief getCurrentPhase Get the current match phase
     * @return 
     */
    MatchPhase getCurrentPhase() {
        return phase;
    }
    
    /**
     * @brief Returns true if a match is in progress, otherwise returns false
     */
    bool isInMatch() {
        return phase == Autonomous || phase == Teleop;
    }
    
    /**
     * @brief autonomousTime The time, in seconds, to spend in autonomous mode
     */
    static const double autonomousTime;
    /**
     * @brief teleopTime The time, in seconds, to spend in teleoperated mode
     */
    static const double teleopTime;
    
protected:
    
    void timerEvent(QTimerEvent *);
    
    /**
     * @brief matchTimerId Qt timer ID for the match timer
     */
    int matchTimerId;
    
    /**
     * @brief phase The current match phase
     */
    MatchPhase phase;
    
    /**
     * @brief elapsedTimer used to keep track of the time elapsed in a match
     */
    QElapsedTimer elapsedTimer;
    
    /**
     * @brief doTeleopStart Emits signals and changes things as appropriate for
     * the end of autonomous and the beginning of teleop
     */
    void doTeleopStart();
    
    /**
     * @brief doMatchEnd Emits signals and changes things as appropriate for
     * the end of the match
     */
    void doMatchEnd();
    
signals:
    
    /**
     * @brief matchStarted Emitted when a match starts
     */
    void matchStarted();
    
    /**
     * @brief autonomousStarted Emitted immediately after matchStarted(),
     * when a match starts
     */
    void autonomousStarted();
    
    /**
     * @brief autonomousFinished Emitted when the autonomous period finishes
     */
    void autonomousFinished();
    
    /**
     * @brief teleopStarted Emitted when the teleop period starts, immediately
     * after autonomousFinished()
     */
    void teleopStarted();
    
    /**
     * @brief teleopFinished Emitted when the teleop period finishes
     */
    void teleopFinished();
    
    /**
     * @brief matchFinished Emitted when a match finishes, immediately after
     * teleopFinished()
     */
    void matchFinished();
    
    /**
     * @brief Emitted frequently when the time changes during a match
     * @param millisecondsElapsed The number of milliseconds that have passed
     * since the match started
     */
    void timeChanged(quint64 millisecondsElapsed);
    
public slots:
    
    /**
     * @brief startMatch Start timing a match
     */
    void startMatch();
    
    /**
     * @brief abortMatch Abort the match and disable all the robots
     */
    void abortMatch();
    
};

#endif // MATCHTIMINGMANAGER_H
