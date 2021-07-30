#include "ytRsSolenoidDriver.hpp"

namespace CAN_Device_Lib{

    namespace Device{

        uint8_t ytRsSolenoidDriver::Convert(){
            uint8_t temp=0;
            for(int i=0;i<8;i++){
                temp|=tx_buf_[i]<<i;
            }
            return temp;
        }

        void ytRsSolenoidDriver::Set(uint8_t num,uint8_t status){
            tx_buf_[num] = status;
        }

        void ytRsSolenoidDriver::Update(){
            uint8_t temp = Convert();
            dev_.Write(dev_id_,&temp,1);
        }

    }

}

