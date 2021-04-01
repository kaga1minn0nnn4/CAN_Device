#include "MD_Base.hpp"


namespace CAN_Device_Lib{
  
  namespace Device{
    double MD_Base::v_convert(double v_raw){
      //v_raw[m/s]
      double spin_num = v_raw / (wheel_diameter * PI);
      double pulse = spin_num * encoder_resolution;
      return pulse * t_v_sampling;
    }

    void MD_Base::trapezoid_move(double& v_,double v_target,int16_t t_ms){
      double t = t_ms * 0.001;
      if(v_ < v_target){
        double v_add = (accel * t);
        if((v_add + v_) > v_target){
          v_ = v_target;
        }else{
          v_ += v_add;
        }
      }else if(v_ > v_target){
        double v_add = (-accel * t);
        if((v_add + v_) < v_target){
          v_ = v_target;
        }else{
          v_ += v_add;
        }
      }
    }
    void MD_Base::Move(uint8_t num,MD_Mode_t cmd,double v_target,boolean trapezoid_f){
      double v_ = 0.0;
      if(trapezoid_f){
        trapezoid_move(v[num],v_target,10);
        v_ = v[num];
      }else{
        v_ = v_target;
      }

      uint16_t value_ = abs(static_cast<int16_t>(v_convert(v_)));

      if(value_ > 8191)value_ = 8191;
      
      uint8_t sign;
      if(v_ > 0){
        sign = 0;
      }else{
        sign = 1;
      }

      uint8_t cmd_ = static_cast<uint8_t>(cmd);

      TxBuf.data[num] = (cmd_ << 14) |+ (sign << 13) |+ value_;

      printLog("%5d",value_);
    }

    void MD_Base::Move(uint8_t num,MD_Mode_t cmd,int16_t duty,boolean trapezoid_f){
      double v_ = 0.0;
      if(trapezoid_f){
        trapezoid_move(v[num],static_cast<double>(duty),10);
        v_ = v[num];
      }else{
        v_ = static_cast<double>(duty);
      }

      uint16_t value_ = static_cast<uint16_t>(abs(v_));
      if(value_ > 8191)value_ = 8191;
      
      uint8_t sign;
      if(v_ > 0){
        sign = 0;
      }else{
        sign = 1;
      }

      uint8_t cmd_ = static_cast<uint8_t>(cmd);

      TxBuf.data[num] = (cmd_ << 14) |+ (sign << 13) |+ value_;

      printLog("%5d",value_);
    }

    void MD_Base::Update(){
      dev.Write(DevID,TxBuf.buf,8);

      for(int i = 0;i < 4;i++){
        uint8_t mask_l = (1 << (7 - (i * 2)));
        uint8_t mask_d = (1 << (6 - (i * 2)));
        LimitSW[i] = (status & mask_l) >> (7 - (i * 2));
        DistanceFlag[i] = (status & mask_d) >> (6 - (i * 2));
      }
    }

    uint16_t MD_Base::ReadID()const{
      return (1 << 10) |+ DevID;
    }
    
    void MD_Base::RxHandler(uint8_t data){
      status = data;
    }

    const uint8_t& MD_Base::ReadLimitSW(uint8_t num)const{
      return LimitSW[num];
    }

    const uint8_t& MD_Base::ReadDistanceFlag(uint8_t num)const{
      return DistanceFlag[num];
    }
  }

}