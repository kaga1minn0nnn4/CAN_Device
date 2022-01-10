#ifndef EVOZK_HPP
#define EVOZK_HPP

#include "CAN_Device.hpp"

typedef union{
    uint8_t buf[5];
    struct{
        uint8_t req;
        float gain;//4byte
    }__packed pid_data;
    struct{
        uint8_t req;
        int32_t value;//4byte
    }__packed data;
}md_send_t;

enum class md_mode_t{
    Duty = 0,
    Speed,
    Angle,
    SetGainKp,
    SetGainKi,
    SetGainKd,
    ReverseDir,
    ResetEncoder
};

namespace CAN_Device_Lib{
  namespace Device{
    class Evozk{
      static constexpr uint16_t kPwmResolution = 0x1ff;
      static constexpr double kEncoderSamplingT = 10.0e-3;//10ms

      uint16_t enc_resolution = 2048;

      CAN_Device& dev_;
      uint16_t dev_id_;
    public:
      Evozk(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id}{}
      uint16_t ReadID()const;

      void SetEncoderResolution(uint16_t value){
        enc_resolution = value;
      }

      void SetPidGain(float kp,float ki,float kd);

      void MoveDuty(int16_t duty);
      void MoveRpm(int16_t rpm);
      void MoveAngle(int16_t angle);

      uint16_t GetPwmResolution()const{
          return kPwmResolution;
      }
    };
  }
}

#endif