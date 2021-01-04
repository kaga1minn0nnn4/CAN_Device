#ifndef DEV_SERVO_H
#define DEV_SERVO_H

#include "Device.hpp"

namespace CAN_Device_Lib{
  
  namespace Device{
  
    class DevServo{
      CAN_Device& dev;
      uint16_t DevID;
      std::vector<uint8_t> ServoDeg;

      uint8_t status;
      uint8_t SW[8];
    public:
      DevServo(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},ServoDeg(4){}
      void Move(uint8_t num,uint8_t deg);
      void Update();

      uint16_t ReadID()const;
      void RxHandler(uint8_t data);

      const uint8_t& ReadSW(uint8_t num)const;
    };

  }

}

#endif