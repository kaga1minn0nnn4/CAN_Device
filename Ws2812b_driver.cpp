#include "Ws2812b_driver.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    void Ws2812b_driver::Update(uint8_t num,uint8_t r,uint8_t g,uint8_t b,uint8_t leds_len){
      uint8_t buf[5] = {num,r,g,b,leds_len};
      dev_.Write(dev_id_,buf,5);
    }
  }
}