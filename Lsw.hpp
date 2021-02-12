#ifndef LSW_H
#define LSW_H

#include "Device.hpp"

namespace CAN_Device_Lib{
    
    namespace Device{

        class Lsw{
            CAN_Device& dev;
            uint16_t DevID;
        public:
            Lsw(CAN_Device& dev,uint16_t id):dev{dev},DevID{id}{}
            void Update(uint8_t p_sw_1,uint8_t p_sw_2);
        };

    }

}

#endif