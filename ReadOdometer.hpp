#ifndef ODO_H
#define ODO_H

#include "Device.hpp"
#include "bno055.hpp"

#define DEBUG_READ_ODOMETER

constexpr double degreeToRadian(double deg){
  //degree -> radian
  return (deg/180.0)*PI;
}
namespace CAN_Device_Lib{
    
  namespace Device{

    /*           Y
                 ^
                 |
                 |
                -|---------->X
v0 tim1
v1 tim2
v2 tim3
v3 tim4


                v1
               <---
                 |
                 |
                 |            ^
 v2 |-------------------------|  v4
    v            |              
                 |
                 |
               --->
                v3
    */

    union ReadOdometer_data_t{
      uint8_t buf[8];
      int16_t pos[4];
    };

    class ReadOdometer{
      static constexpr double encoder_resolution = 2048.0;
      static constexpr double t_sample = 10.0e-3;//s
      static constexpr double wheel_diameter = 52.0e-3;//m
      static constexpr double kLPF = 0.10;

      bno055Lib::bno055 imu;

      CAN_Device& dev;
      uint16_t DevID;

      ReadOdometer_data_t DevData;

      int16_t pos_last[4];

      double Vx;
      double Vy;

      double X;
      double Y;
      double Angle;

      double v_convert(int16_t pulse);

      int16_t encoder_filter(int16_t raw,int16_t lpf_last);

      template <typename... T>inline __attribute__((always_inline)) void printLog(T... args){
        #ifdef DEBUG_READ_ODOMETER
        printf(args...);
        #endif
      }
    public:
      ReadOdometer(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},DevData{},pos_last{},Vx{0.0},Vy{0.0},X{0.0},Y{0.0},Angle{0.0}{}
      void RxHandler(const std::vector<uint8_t>& data);

      void setup();
      void update();

      uint16_t ReadID()const;

      const double& GetVx()const{
        return Vx;
      }

      const double& GetVy()const{
        return Vy;
      }

      const double& GetX()const{
        return X;
      }

      const double& GetY()const{
        return Y;
      }
      
      const double& GetAngle()const{
        return Angle;
      }

      void Reset(){
        for(auto& enc:pos_last){
          enc = 0;
        }
        X = 0.0;
        Y = 0.0;
        Vx = 0.0;
        Vy = 0.0;
      }
    };

  }

}

#endif