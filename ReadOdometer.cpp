#include "ReadOdometer.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    void ReadOdometer::RxHandler(std::vector<uint8_t> data){
      if(data.size()<8)return;

      for(int i=0;i<8;i++)DevData.buf[i] = data[i];

      X = DevData.pos[0];
      Y = DevData.pos[1];
    }

    uint16_t ReadOdometer::ReadID()const{
      return (1 << 10) |+ DevID;
    }

    const int32_t& ReadOdometer::GetX()const{
      return X;
    }

    const int32_t& ReadOdometer::GetY()const{
      return Y;
    }
    
  }

}