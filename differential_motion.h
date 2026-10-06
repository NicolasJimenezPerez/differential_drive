#ifndef __MOTOR_CONTROLLER_H__
#define __MOTOR_CONTROLLER_H__


#include <inttypes.h>

#include <HardwareSerial.h>
#ifdef __AVR__
	#include <SoftwareSerial.h>
#endif

#include "differential_speed.h"


struct DifferentialMotionGeometry
{
    float wheelLength_mm;
    float wheelWidth_mm;
    float wheelRadius_mm;
    uint16_t encoderPulsesPerRev;
    float motorSpeedReductionFactor = 1; 
};


class DifferentialMotion
{

protected:


    
    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                       Protected variables                      ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////



    /// @brief Flag to check if the geometry is configured
    bool isConfigured = false;

    /// @brief Confersion factor from m/s to the command the motor controller expects
    float m_s_toMotorCommand;

    /// @brief Confersion factor from radians to the command the motor controller expects
    float rad_toMotorCommand;


public:



    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                          Public Methods                        ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////



    /// @brief Method to setup the differential speed with hardware serial
    /// @param uart Reference to the serial handler to communicate with the controllers
    /// @param addrFront Address for the front motor controller
    /// @param addrRear Address for the rear motor controller
    /// @param timeout_us Serial timeout in microseconds
    virtual void setup(HardwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us = 10000) = 0;

#ifdef __AVR__
    /// @brief Method to setup the differential speed with software serial
    /// @param uart Reference to the serial handler to communicate with the controllers
    /// @param addrFront Address for the front motor controller
    /// @param addrRear Address for the rear motor controller
    /// @param timeout_us Serial timeout in microseconds
    virtual void setup(SoftwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us = 10000) = 0;
#endif

    /// @brief Configuration of the differential motion
    /// @param geometry Geometry of the robot
    virtual void config(const DifferentialMotionGeometry& geometry) = 0;

    /// @brief Method to set the differential speed
    /// @param differentialSpeed The speed to be set
    virtual void setSpeed(const DifferentialSpeed& differentialSpeed) = 0;

};


#endif