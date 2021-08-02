#include "MD_Base.hpp"


namespace CAN_Device_Lib{
  
  namespace Device{
    double MD_Base::VConvert(double v_raw){
      //v_raw[m/s]
      double spin_num = v_raw / (kWheelDiameter * PI);
      double pulse = spin_num * kEncoderResolution;
      return pulse * kTVSampling;
    }

    void MD_Base::TrapezoidMove(double& v_,double v_target,int16_t t_ms){
      double t = t_ms * 0.001;
      if(v_ < v_target){
        double v_add = (kAccel * t);
        if((v_add + v_) > v_target){
          v_ = v_target;
        }else{
          v_ += v_add;
        }
      }else if(v_ > v_target){
        double v_add = (-kAccel * t);
        if((v_add + v_) < v_target){
          v_ = v_target;
        }else{
          v_ += v_add;
        }
      }
    }
    void MD_Base::Move(uint8_t num,MD_Mode_t cmd,double v_target,boolean trapezoid_f){
      double v = 0.0;
      if(trapezoid_f){
        TrapezoidMove(v_[num],v_target,10);
        v = v_[num];
      }else{
        v = v_target;
      }

      uint16_t value = abs(static_cast<int16_t>(VConvert(v)));

      if(value > 2047)value = 2047;
      
      uint8_t sign;
      if(v > 0){
        sign = 0;
      }else{
        sign = 1;
      }

      uint8_t check = 0b11;
      uint8_t cmd_cast = static_cast<uint8_t>(cmd);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (check << 11) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::Move(uint8_t num,MD_Mode_t cmd,int16_t duty,boolean trapezoid_f){
      double v = 0.0;
      if(trapezoid_f){
        TrapezoidMove(v_[num],static_cast<double>(duty),10);
        v = v_[num];
      }else{
        v = static_cast<double>(duty);
      }

      uint16_t value = static_cast<uint16_t>(abs(v));
      if(value > 2047)value = 2047;
      
      uint8_t sign;
      if(v > 0){
        sign = 0;
      }else{
        sign = 1;
      }
      uint8_t check = 0b11;
      uint8_t cmd_cast = static_cast<uint8_t>(cmd);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (check << 11) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::MoveRpm(uint8_t num,int32_t rpm){
      double rpm_target = abs((static_cast<double>(rpm) / 60.0) * kTVSampling);

      uint16_t value = static_cast<uint16_t>(rpm_target * kEncoderResolution);
      
      uint8_t sign;
      if(rpm > 0){
        sign = 0;
      }else{
        sign = 1;
      }
      
      uint8_t cmd = static_cast<uint8_t>(MD_Mode_t::SpeedMode);
      uint8_t check = 0b11;
      uint8_t cmd_cast = static_cast<uint8_t>(cmd);

      tx_buf_.data[num] = (cmd_cast << 14) |+ (sign << 13) |+ (check << 11) |+ value;

      printLog("%5d",value);
    }

    void MD_Base::Update(){
      dev_.Write(dev_id_,tx_buf_.buf,8);

      for(int i = 0;i < 4;i++){
        uint8_t mask_l = (1 << (7 - (i * 2)));
        uint8_t mask_d = (1 << (6 - (i * 2)));
        limit_sw_[i] = (status_ & mask_l) >> (7 - (i * 2));
        distance_flag_[i] = (status_ & mask_d) >> (6 - (i * 2));
      }
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
    
    void MD_Base::RxHandler(uint8_t data){
      status_ = data;
    }

    const uint8_t& MD_Base::ReadLimitSW(uint8_t num)const{
      return limit_sw_[num];
    }

    const uint8_t& MD_Base::ReadDistanceFlag(uint8_t num)const{
      return distance_flag_[num];
    }
  }

}