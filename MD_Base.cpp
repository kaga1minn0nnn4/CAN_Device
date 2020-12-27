#include "MD_Base.hpp"


namespace CAN_Device_Lib{
  
  namespace Device{

    void MD_Base::Move(uint8_t num,MD_Mode_t cmd,int16_t value){
      uint16_t value_ = abs(value);
      if(value_ > 8191)value_ = 8191;
      
      uint8_t sign;
      if(value > 0){
        sign = 0;
      }else{
        sign = 1;
      }

      uint8_t cmd_ = static_cast<uint8_t>(cmd);

      TxBuf.data[num] = (cmd_ << 14) |+ (sign << 13) |+ value_;

    }

    void MD_Base::Update(){
      dev.Write(DevID,TxBuf.buf,8);
    }

    uint16_t MD_Base::ReadID(){
        return (1 << 10) |+ DevID;
    }
    
    void MD_Base::RxHandler(uint8_t data){
        status = data;
    }
  }

}