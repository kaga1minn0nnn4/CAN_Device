#include "ReadOdometer.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    double ReadOdometer::v_convert(int16_t pulse){
      double spin_num = static_cast<double>(pulse) / encoder_resolution;
      double distance = spin_num * (wheel_diameter * PI);
      return distance / t_sample;
    }

    void ReadOdometer::RxHandler(const std::vector<uint8_t>& data){
      if(data.size()<8)return;

      for(int i=0;i<8;i++)DevData.buf[i] = data[i];
      DevData.pos[3] = -DevData.pos[3];
      for(auto& x:DevData.pos){
        if(abs(x) <= 1){
          x = 0;
        }
      }
      double v[4] = {
        v_convert(DevData.pos[0]) / 2.0,
        v_convert(DevData.pos[1]) / 2.0,
        v_convert(DevData.pos[2]) / 2.0,
        v_convert(DevData.pos[3]) / 2.0
      };
      
      double Vx = v[0] * cos(Angle + PI) + v[1] * cos(Angle - (PI / 2.0)) + v[2] * cos(Angle) + v[3] * cos(Angle + (PI / 2.0));
      double Vy = v[0] * sin(Angle + PI) + v[1] * sin(Angle - (PI / 2.0)) + v[2] * sin(Angle) + v[3] * sin(Angle + (PI / 2.0));

      X += Vx * t_sample;
      Y += Vy * t_sample;
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