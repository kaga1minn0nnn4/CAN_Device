#ifndef LSW_H
#define LSW_H

#include "Device.hpp"

namespace CAN_Device_Lib{
    
    namespace Device{

        class Lsw{
            CAN_Device& dev_;
            uint16_t dev_id_;
        public:
            Lsw(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id}{}
            void Update(uint8_t p_sw_1,uint8_t p_sw_2);
        };

    }

}

#endif