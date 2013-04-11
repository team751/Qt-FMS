#ifndef FMSDEFS_H
#define FMSDEFS_H

/**
 * @brief The FMSDefs class is a utility class that defines commonly used enumerations.
 */
class FMSDefs {
    
public:
    
    /**
     * @brief The AllianceColor enum defines values for the red and blue alliances
     */
    enum AllianceColor {
        RedAlliance = 0x52,
        BlueAlliance = 0x42,
    };
    
    /**
     * @brief The DriverStationNumber enum defines values for driver station positions 1-3
     */
    enum DriverStationNumber {
        Station1 = 0x31,
        Station2 = 0x32,
        Station3 = 0x33,
    };
    
    /**
     * @brief The RobotState enum defines robot modes and enabled/disabled states
     */
    enum RobotState {
        //These two statuses are only sent from driver stations to the FMS
        //when they do not have robot communication
        AutonomousNoCommunication = 0x51,
        TeleopNoCommunication = 0x41,
        //The foloowing statuses are sent both ways, but their numerical values
        //are only valid for packets from the FMS to driver stations.
        AutonomousDisabled = 0x53,
        AutonomousEnabled = 0x53 + 0x20,
        TeleopDisabled = 0x43,
        TeleopEnabled = 0x43 + 0x20,
    };
    
    
private:
    FMSDefs() {}
};

#endif // FMSDEFS_H
