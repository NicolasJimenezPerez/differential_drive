#ifndef __DIFFERENTIAL_MOTION_ROBOCLAWS_H__
#define __DIFFERENTIAL_MOTION_ROBOCLAWS_H__


#include "differential_motion.h"

#include <basicmicro.h>


class DifferentialMotionRoboclaws : public DifferentialMotion
{



    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                        Private Variables                       ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////



    /// @brief Address for the front roboclaw
    uint8_t addrFront = 0;

    /// @brief Address for the rear roboclaw
    uint8_t addrRear = 0;
    
    /// @brief Pointer to the basicmicro object
    Basicmicro *p_basicmicro = nullptr;
    
    /// @brief Flag to know if the roboclaws are used with hardware or software serial
    bool isHardwareSerial = true; 

    /// @brief Pointer to the serial object
    void *p_uart = nullptr;


public:



    ////////////////////////////////////////////////////////////////////////
    ////                                                                ////
    ////                         Public Methods                         ////
    ////                                                                ////
    ////////////////////////////////////////////////////////////////////////



    /// @brief Method to setup the differential speed with hardware serial
    /// @param uart Reference to the serial handler to communicate with the controllers
    /// @param addrFront Address for the front motor controller
    /// @param addrRear Address for the rear motor controller
    /// @param timeout_us Serial timeout in microseconds
    virtual void setup(HardwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us = 10000) override;

#ifdef __AVR__
    /// @brief Method to setup the differential speed with software serial
    /// @param uart Reference to the serial handler to communicate with the controllers
    /// @param addrFront Address for the front motor controller
    /// @param addrRear Address for the rear motor controller
    /// @param timeout_us Serial timeout in microseconds
    virtual void setup(SoftwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us = 10000) override;
#endif

    /// @brief Configuration of the differential motion
    /// @param geometry Geometry of the robot
    virtual void config(const DifferentialMotionGeometry& geometry) override;

    /// @brief 
    /// @param speed 
    virtual void setSpeed(const DifferentialSpeed& speed) override;

};


#endif