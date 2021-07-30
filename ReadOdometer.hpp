#ifndef ODO_H
#define ODO_H

#include "Device.hpp"
#include "bno055.hpp"

//#define DEBUG_READ_ODOMETER

constexpr double degree_to_radian(double deg){
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
      static constexpr double kEncoderResolution = 2048.0;
      static constexpr double kTSample = 10.0e-3;//s
      static constexpr double kWheelDiameter = 52.0e-3;//m
    
      Bno055Lib::Bno055 imu_;

      CAN_Device& dev_;
      uint16_t dev_id_;

      ReadOdometer_data_t dev_data_;

      double vx_;
      double vy_;

      double x_;
      double y_;
      double angle_;

      double VConvert(int16_t pulse);

      template <typename... T>inline __attribute__((always_inline)) void printLog(T... args){
        #ifdef DEBUG_READ_ODOMETER
        printf(args...);
        #endif
      }
    public:
      ReadOdometer(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id},dev_data_{},vx_{0.0},vy_{0.0},x_{0.0},y_{0.0},angle_{0.0}{}
      void RxHandler(const std::vector<uint8_t>& data);

      void Setup();
      void Update();

      uint16_t ReadID()const;

      const double& GetVx()const{
        return vx_;
      }

      const double& GetVy()const{
        return vy_;
      }

      const double& GetX()const{
        return x_;
      }

      const double& GetY()const{
        return y_;
      }
      
      const double& GetAngle()const{
        return angle_;
      }

      void Reset(){
        x_ = 0.0;
        y_ = 0.0;
        vx_ = 0.0;
        vy_ = 0.0;
      }
    };

  }

}

#endif