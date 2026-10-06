#include "differential_motion_roboclaws.h"


void DifferentialMotionRoboclaws::setup(HardwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us)
{
    if (nullptr != p_basicmicro)
        delete p_basicmicro;

    p_uart = (void *)&uart;

    p_basicmicro = new Basicmicro(&uart, timeout_us);
    isHardwareSerial = true; 

    this->addrFront = addrFront;
    this->addrRear = addrRear;
}


#ifdef __AVR__
void DifferentialMotionRoboclaws::setup(SoftwareSerial& uart, uint8_t addrFront, uint8_t addrRear, uint32_t timeout_us)
{
    if (nullptr != p_basicmicro)
        delete p_basicmicro;

    p_uart = (void *)&uart;
    isHardwareSerial = false; 

    p_basicmicro = new Basicmicro(&uart, timeout_us);

    this->addrFront = addrFront;
    this->addrRear = addrRear;
}
#endif


void DifferentialMotionRoboclaws::config(const DifferentialMotionGeometry& geometry)
{
    float motorRevToLin = geometry.encoderPulsesPerRev * geometry.motorSpeedReductionFactor / geometry.wheelRadius_mm;
    m_s_toMotorCommand = 1000.0f * motorRevToLin;
    rad_toMotorCommand = sqrtf(geometry.wheelLength_mm * geometry.wheelLength_mm + geometry.wheelWidth_mm * geometry.wheelWidth_mm) * motorRevToLin * M_1_PI;
    

    isConfigured = true;
}


void DifferentialMotionRoboclaws::setSpeed(const DifferentialSpeed& differentialSpeed)
{
    if (nullptr == p_basicmicro)
        return;

    if (nullptr == p_uart)
        return;

    if (isHardwareSerial)
    {
        if (!*(HardwareSerial *)p_uart)
            return;
    }
#ifdef __AVR__
    else if (!*(SoftwareSerial *)p_uart)
        return;
#endif

    // Set values
    int16_t linearPulses = differentialSpeed.linear_m_s * m_s_toMotorCommand;
    int16_t angularPulses = differentialSpeed.angular_rad_s * rad_toMotorCommand;
    p_basicmicro->SpeedM1M2(addrFront, linearPulses - angularPulses, linearPulses + angularPulses);
    p_basicmicro->SpeedM1M2(addrRear, linearPulses + angularPulses, linearPulses - angularPulses);
}
