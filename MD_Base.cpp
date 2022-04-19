#include "MD_Base.hpp"


namespace CAN_Device_Lib{
  
  namespace Device{

    void MD_Base::MoveDuty(uint8_t num,int16_t duty,uint8_t dir){
      uint16_t value = abs(duty);
      if(value > 2047)value = 2047;
      
      uint8_t sign;
      if(duty > 0){
        sign = 0;
      }else{
        sign = 1;
      }

      uint8_t cmd_cast = static_cast<uint8_t>(MD_Mode_t::DutyMode);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (dir << 12) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::MoveRpm(uint8_t num,int32_t rpm,uint8_t dir){
      double rpm_target = abs((static_cast<double>(rpm) / 60.0) * kTVSampling);

      uint16_t value = static_cast<uint16_t>(rpm_target * encoder_resolution_);

      uint8_t sign;
      if(rpm > 0){
        sign = 0;
      }else{
        sign = 1;
      }
    
      uint8_t cmd_cast = static_cast<uint8_t>(MD_Mode_t::SpeedMode);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (dir << 12) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::MoveDistance(uint8_t num,int32_t distance,uint8_t dir){
      uint16_t value = abs(distance / 10);

      uint8_t sign;
      if(distance > 0){
        sign = 0;
      }else{
        sign = 1;
      }
    
      uint8_t cmd_cast = static_cast<uint8_t>(MD_Mode_t::DistanceMode);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (dir << 12) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::Update(){
      dev_.Write(dev_id_,tx_buf_.buf,8);
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
  }

}