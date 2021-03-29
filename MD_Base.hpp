#ifndef MD_BASE_H
#define MD_BASE_H

#include "Device.hpp"
#include <cstdio>

#define DEBUG_MD_BASE

namespace CAN_Device_Lib{
  
  namespace Device{

    enum class MD_Mode_t{
      DutyMode = 0,
      SpeedMode,
      DistanceMode,
      ResetMode
    };

    union MD_Base_Data_t{
      uint8_t buf[8];
      uint16_t data[4];      
    };
  
    class MD_Base{
      static constexpr double accel = 1.0; //[m/s^2]
      static constexpr double v_max = 1.0; //[m/s]

      static constexpr double wheel_diameter = 120 * 10e-3;//[sm]
      static constexpr double t_v_sampling = 9.984 * 10e-3;//[s]

      CAN_Device& dev;
      uint16_t DevID;
      MD_Base_Data_t TxBuf;
      uint8_t status;

      uint8_t DistanceFlag[4];
      uint8_t LimitSW[4];

      std::vector<double> v;

      double v_convert(double v_raw);
      void trapezoid_move(double& v_,double v_target,int16_t t_ms);

      template <typename... T>void printLog(T... args){
#ifdef DEBUG_MD_BASE
        std::printf(args...);
#endif
      }
    public:
      MD_Base(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},TxBuf{},status{0},v(4,0.0){}
      void Move(uint8_t num,MD_Mode_t cmd,double v_target);
      void Move(uint8_t num,MD_Mode_t cmd,int16_t duty);
      void Update();

      uint16_t ReadID()const;
      void RxHandler(uint8_t data);

      const uint8_t& ReadLimitSW(uint8_t num)const;
      const uint8_t& ReadDistanceFlag(uint8_t num)const;
    };

  }

}

#endif