#include "Device.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    class Ws2812b_driver{
      CAN_Device& dev_;
      uint16_t dev_id_;
    public:
      Ws2812b_driver(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id}{}
      void Update(uint8_t num,uint8_t r,uint8_t g,uint8_t b,uint8_t leds_len);
    };
  }
}