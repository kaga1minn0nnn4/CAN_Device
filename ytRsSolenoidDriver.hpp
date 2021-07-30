#ifndef YTRS_H
#define YTRS_H

#include "Device.hpp"

namespace CAN_Device_Lib{
    
    namespace Device{

        class ytRsSolenoidDriver{
            CAN_Device& dev_;
            uint16_t dev_id_;
            uint8_t tx_buf_[8];
            uint8_t Convert();
        public:
            ytRsSolenoidDriver(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id},tx_buf_{0,0,0,0,0,0,0,0}{}
            void Set(uint8_t num,uint8_t status);
            void Update();
        };

    }

}


#endif