#ifndef ODO_H
#define ODO_H

#include "Device.hpp"

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


                v0
                --->
                 |
                 |
    ^            |            
 v3 |-------------------------|  v1
                 |            v   
                 |
                 |
               <---
                v2
    */

    union ReadOdometer_data_t{
      uint8_t buf[8];
      int16_t pos[4];
    };

    class ReadOdometer{
      CAN_Device& dev;
      uint16_t DevID;

      ReadOdometer_data_t DevData;

      double X;
      double Y;
    public:
      ReadOdometer(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},DevData{},X{0.0},Y{0.0}{}
      void RxHandler(const std::vector<uint8_t>& data);

      uint16_t ReadID()const;

      const double& GetX()const;
      const double& GetY()const;
    };

  }

}

#endif