#ifndef MD_BASE_H
#include "Device.hpp"


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
      CAN_Device& dev;
      uint16_t DevID;
      MD_Base_Data_t TxBuf;
      uint8_t status;
    public:
      MD_Base(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},TxBuf{}{}
      void Move(uint8_t num,MD_Mode_t cmd,int16_t value);
      void Update();
      uint16_t ReadID();
      void RxHandler(uint8_t data);
    };

  }

}

#endif