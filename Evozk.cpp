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

        delay(kSetupDelay);
      }
    }

    void Evozk::MoveDuty(int16_t duty){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::Duty);
      tx.data.value = duty;
      printLog("%d\n",tx.data.value);

      dev_.Write(dev_id_,tx.buf,5);
    }

    void Evozk::MoveRpm(int16_t rpm){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::Speed);  
      tx.data.value = static_cast<int16_t>(static_cast<double>(rpm * enc_resolution) / 60.0 * kEncoderSamplingT);
      printLog("%d\n",tx.data.value);

      dev_.Write(dev_id_,tx.buf,5);
    }

    void Evozk::MoveAngle(int16_t angle){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::Angle);
      tx.data.value = static_cast<int16_t>(static_cast<double>(angle * enc_resolution) / 360.0);

      printLog("%d\n",tx.data.value);
      dev_.Write(dev_id_,tx.buf,5);
    }

    void Evozk::ResetEncoder(){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::ResetEncoder);
      tx.data.value = 193;
      dev_.Write(dev_id_,tx.buf,5);
      delay(kSetupDelay);
    }

    void Evozk::SetDirection(uint8_t dir){
      md_send_t tx{};
      tx.data.req = static_cast<uint8_t>(md_mode_t::SetDir);
      tx.data.value = dir;
      dev_.Write(dev_id_,tx.buf,5);
      delay(kSetupDelay);
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
  }
}