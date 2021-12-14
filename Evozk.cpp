#include "Evozk.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    void Evozk::MoveDuty(int16_t duty){
      byte2_convert_t tx{};
      tx.data = duty;
      if(duty > kPwmResolution){
        duty = kPwmResolution;
      }else if(duty < -kPwmResolution){
        duty = -kPwmResolution;
      }

      dev_.Write(dev_id_,tx.buf,2);
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
  }
}