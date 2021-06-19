#include "pureToF.hpp"


namespace CAN_Device_Lib{

  namespace Device{

    void PureToF::RxHandler(std::vector<uint8_t> data){
      if(data.size() != 4){
        return;
      } 
      for(int i = 0;i < 4;i++){
        ranging.buf[i] = data[i];
      }
    }

    uint16_t PureToF::ReadID()const{
      return (1 << 10) |+ DevID;
    }

    int16_t PureToF::ReadRangingData()const{
      return ranging.data;
    }
    
  }

}