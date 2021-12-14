#ifndef EVOZK_HPP
#define EVOZK_HPP

#include "CAN_Device.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    class Evozk{
      static constexpr uint16_t kPwmResolution = 0x7ff;

      CAN_Device& dev_;
      uint16_t dev_id_;
    public:
      Evozk(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id}{}
      uint16_t ReadID()const;
      void MoveDuty(int16_t duty);

      uint16_t GetPwmResolution()const{
          return kPwmResolution;
      }
    };
  }
}

#endif