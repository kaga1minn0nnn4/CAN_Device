#include "ReadOdometer.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    double ReadOdometer::VConvert(int16_t pulse){
      double spin_num = static_cast<double>(pulse) / kEncoderResolution;
      double distance = spin_num * (kWheelDiameter * PI);
      return distance / kTSample;
    }

    void ReadOdometer::RxHandler(const std::vector<uint8_t>& data){
      if(data.size()<8)return;
      
      for(int i=0;i<8;i++)dev_data_.buf[i] = data[i];

      int16_t pos_lpf[4];

      double v[4] = {
        -VConvert(pos_lpf[0]),
        -VConvert(pos_lpf[1]),
        -VConvert(pos_lpf[2]),
        -VConvert(pos_lpf[3])
      };
      
      vx_ = (v[0] * cos(angle_ + PI) + v[1] * cos(angle_ - (PI / 2.0)) + v[2] * cos(angle_) + v[3] * cos(angle_ + (PI / 2.0))) / 8.0;
      vy_ = (v[0] * sin(angle_ + PI) + v[1] * sin(angle_ - (PI / 2.0)) + v[2] * sin(angle_) + v[3] * sin(angle_ + (PI / 2.0))) / 8.0;

      x_ += vx_;
      y_ += vy_;

      printLog(" Vx : %6.3f Vy : %6.3f X : %6.3f Y : %6.3f Yaw : %6.3f",vx_,vy_,x_,y_,angle_);
      printLog("\n");
    }

    void ReadOdometer::Setup(){
      imu_.Setup();
    }

    void ReadOdometer::Update(){
      imu_.Update();
      angle_ = degree_to_radian(imu_.GetYaw(1));
    }

    uint16_t ReadOdometer::ReadID()const{
      return (1 << 10) |+ dev_id_;
    }
  }

}