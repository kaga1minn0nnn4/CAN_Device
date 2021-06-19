#include "Device.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    class Ws2812b_driver{
      CAN_Device& dev;
      uint16_t DevID;
    public:
      Ws2812b_driver(CAN_Device& dev,uint16_t id):dev{dev},DevID{id}{}
      void Update(uint8_t num,uint8_t r,uint8_t g,uint8_t b,uint8_t leds_len);
    };
  }
}