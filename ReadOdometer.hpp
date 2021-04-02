#ifndef ODO_H
#define ODO_H

#include "Device.hpp"
#include "bno055.hpp"

namespace CAN_Device_Lib{
    
  namespace Device{

    /*           Y
                 ^
                 |
                 |
                -|---------->X
v0 tim1
v1 tim2
v2 tim3
v3 tim4


                v1
               <---
                 |
                 |
                 |            ^
 v2 |-------------------------|  v4
    v            |              
                 |
                 |
               --->
                v3
    */

    union ReadOdometer_data_t{
      uint8_t buf[8];
      int16_t pos[4];
    };

    class ReadOdometer{
      static constexpr double encoder_resolution = 2048.0;
      static constexpr double t_sample = 10.0e-3;//s
      static constexpr double wheel_diameter = 52.0e-3;//m

      bno055Lib::bno055 imu;

      CAN_Device& dev;
      uint16_t DevID;

      ReadOdometer_data_t DevData;

      double X;
      double Y;
      double Angle;

      double v_convert(int16_t pulse);
    public:
      ReadOdometer(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},DevData{},X{0.0},Y{0.0},Angle{0.0}{}
      void RxHandler(const std::vector<uint8_t>& data);

      void setup();
      void update();

      uint16_t ReadID()const;

      const double& GetX()const{
        return X;
      }

      const double& GetY()const{
        return Y;
      }
      
      const double& GetAngle()const{
        return Angle;
      }
    };

  }

}

#endif