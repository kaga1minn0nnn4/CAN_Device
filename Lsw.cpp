#include "Lsw.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    void Lsw::Update(uint8_t p_sw_1,uint8_t p_sw_2){
      uint8_t temp = (p_sw_1 << 1) |+ p_sw_2;
      dev.Write(DevID,&temp,1);
    }
  }
}