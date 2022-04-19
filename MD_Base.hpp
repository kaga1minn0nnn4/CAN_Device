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
      static constexpr double kTVSampling = 9.984e-3;//[s]

      CAN_Device& dev_;
      uint16_t dev_id_;
      MD_Base_Data_t tx_buf_;

      uint16_t encoder_resolution_;

      template <typename... T>void printLog(T... args){
#ifdef DEBUG_MD_BASE
        std::printf(args...);
#endif
      }
    public:
      MD_Base(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id},tx_buf_{}{}

      void SetEncoderResolution(uint16_t enc){encoder_resolution_ = enc;}

      void MoveDuty(uint8_t num,int16_t duty,uint8_t dir);
      void MoveRpm(uint8_t num,int32_t rpm,uint8_t dir);
      void MoveDistance(uint8_t num,int32_t distance,uint8_t dir);
      
      void Update();

      uint16_t ReadID()const;
    };

  }

}

#endif