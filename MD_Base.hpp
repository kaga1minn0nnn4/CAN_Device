#ifndef MD_BASE_H
#define MD_BASE_H

#include "Device.hpp"
#include <cstdio>

//#define DEBUG_MD_BASE

namespace CAN_Device_Lib{
  
  namespace Device{

    enum class MD_Mode_t{
      DutyMode = 0,
      SpeedMode,
      DistanceMode,
      AngleMode
    };

    union MD_Base_Data_t{
      uint8_t buf[8];
      uint16_t data[4];      
    };
  
    class MD_Base{
      static constexpr double kAccel = 1.0; //[m/s^2]
      static constexpr double kVmax = 1.0; //[m/s]

      static constexpr double kWheelDiameter = 127e-3;//[m]
      static constexpr double kTVSampling = 9.984e-3;//[s]
      static constexpr double kEncoderResolution = 2000;

      CAN_Device& dev_;
      uint16_t dev_id_;
      MD_Base_Data_t tx_buf_;
      uint8_t status_;

      uint8_t distance_flag_[4];
      uint8_t limit_sw_[4];

      std::vector<double> v_;

      double VConvert(double v_raw);
      void TrapezoidMove(double& v_,double v_target,int16_t t_ms);

      template <typename... T>void printLog(T... args){
#ifdef DEBUG_MD_BASE
        std::printf(args...);
#endif
      }
    public:
      MD_Base(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id},tx_buf_{},status_{0},v_(4,0.0){}
      void Move(uint8_t num,MD_Mode_t cmd,double v_target,boolean trapezoid_f = true);
      void Move(uint8_t num,MD_Mode_t cmd,int16_t duty,boolean trapezoid_f = true);
      void MoveRpm(uint8_t num,int32_t rpm);
      void Update();

      uint16_t ReadID()const;
      void RxHandler(uint8_t data);

      const uint8_t& ReadLimitSW(uint8_t num)const;
      const uint8_t& ReadDistanceFlag(uint8_t num)const;
    };

  }

}

#endif