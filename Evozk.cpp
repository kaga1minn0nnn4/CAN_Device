#include "Evozk.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    void Evozk::SetPidGain(float kp,float ki,float kd){
      md_send_t tx{};
      float gain[3] = {kp,ki,kd};

      for(int i = 0;i < 3;i++){
        tx.pid_data.req = i + static_cast<uint8_t>(md_mode_t::SetGainKp);
        tx.pid_data.gain = gain[i];

        dev_.Write(dev_id_,tx.buf,5);

        delay(20);
      }
    }

    void Evozk::MoveDuty(int16_t duty){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::Duty);
      tx.data.value = duty;

      for(int i = 0;i < 5;i++){
        printf("%4d",tx.buf[i]);
      }
      printf("\n");

      dev_.Write(dev_id_,tx.buf,5);
    }

    void Evozk::MoveRpm(int16_t rpm){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::Speed);  
      tx.data.value = static_cast<double>(rpm) / 60.0 * kEncoderSamplingT;

      dev_.Write(dev_id_,tx.buf,5);
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
  }
}