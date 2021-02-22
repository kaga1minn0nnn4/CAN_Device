#include "ReadOdometer.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    void ReadOdometer::RxHandler(std::vector<uint8_t> data){
      if(data.size()<8)return;

      for(int i=0;i<8;i++)DevData.buf[i] = data[i];
      X += ((0.152 / 2.0) * (double)(1 * DevData.pos[0] + 0 * DevData.pos[1] + (-1) * DevData.pos[2] + 0 * DevData.pos[3])) * 0.01;
      Y += ((0.152 / 2.0) * (double)(0 * DevData.pos[0] + (-1) * DevData.pos[1] + 0 * DevData.pos[2] + 1 * DevData.pos[3])) * 0.01;
      
    }

    uint16_t ReadOdometer::ReadID()const{
      return (1 << 10) |+ DevID;
    }

    const double& ReadOdometer::GetX()const{
      return X;
    }

    const double& ReadOdometer::GetY()const{
      return Y;
    }
    
  }

}