#include "ReadOdometer.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    double ReadOdometer::v_convert(int16_t pulse){
      double spin_num = static_cast<double>(pulse) / encoder_resolution;
      double distance = spin_num * (wheel_diameter * PI);
      return distance / t_sample;
    }

    int16_t ReadOdometer::encoder_filter(int16_t raw,int16_t lpf_last){
      int16_t lpf;
      lpf = static_cast<int16_t>((1.0 - kLPF) * static_cast<double>(lpf_last) + kLPF * static_cast<double>(raw));
      if(abs(lpf) <= 1){
        lpf = 0;
      }
      return lpf;
    }

    void ReadOdometer::RxHandler(const std::vector<uint8_t>& data){
      if(data.size()<8)return;

      for(int i=0;i<8;i++)DevData.buf[i] = data[i];

      double k = 0.1;

      int16_t pos_lpf[4];
      for(int i = 0;i < 4;i++){
        pos_lpf[i] = encoder_filter(DevData.pos[i],pos_last[i]);
        pos_last[i] = pos_lpf[i];
        printLog("%5d",pos_lpf[i]);
      }

      double v[4] = {
        v_convert(pos_lpf[0]),
        v_convert(pos_lpf[1]),
        v_convert(pos_lpf[2]),
        v_convert(pos_lpf[3])
      };
      
      Vx = (v[0] * cos(Angle + PI) + v[1] * cos(Angle - (PI / 2.0)) + v[2] * cos(Angle) + v[3] * cos(Angle + (PI / 2.0))) / 2.0;
      Vy = (v[0] * sin(Angle + PI) + v[1] * sin(Angle - (PI / 2.0)) + v[2] * sin(Angle) + v[3] * sin(Angle + (PI / 2.0))) / 2.0;

      X += Vx;
      Y += Vy;

      printLog(" Vx : %6.3f Vy : %6.3f X : %6.3f Y : %6.3f",Vx,Vy,X,Y);
      printLog("\n");
    }

    void ReadOdometer::setup(){
      imu.setup();
    }

    void ReadOdometer::update(){
      imu.update();
      Angle = degreeToRadian(imu.GetYaw(1));
    }

    uint16_t ReadOdometer::ReadID()const{
      return (1 << 10) |+ DevID;
    }
  }

}