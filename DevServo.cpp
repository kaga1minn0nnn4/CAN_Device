#include "DevServo.hpp"

namespace CAN_Device_Lib{
  
  namespace Device{

    void DevServo::Move(uint8_t num,uint8_t deg){
      if((deg > 180) || (num > 3))return;
      ServoDeg[num] = deg;
    }

    void DevServo::Update(){
      dev.Write(DevID,ServoDeg);

      for(int i = 0;i < 8;i++){
        uint8_t mask = 1 << i;
        SW[i] = (status & mask) >> i;
      }
    }

    uint16_t DevServo::ReadID()const{
      return (1 << 10) |+ DevID;
    }

    void DevServo::RxHandler(uint8_t data){
      status = data;
    }

    const uint8_t& DevServo::ReadSW(uint8_t num)const{
      if(num > 7)return 0;
      return SW[num];
    }

  }

}