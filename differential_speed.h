#ifndef __DIFFERENTIAL_SPEED_H__
#define __DIFFERENTIAL_SPEED_H__


struct DifferentialSpeed
{

    /// @brief Stores the linear component of the speed in m/s
    float linear_m_s = 0;

    /// @brief Stores the angular component of the speed in rad/s
    float angular_rad_s = 0;
    
};


#endif