#include "ytRsSolenoidDriver.hpp"

uint8_t ytRsSolenoidDriver::Convert(){
    uint8_t temp=0;
    for(int i=0;i<8;i++){
        temp|=TxBuf[i]<<i;
    }
    return temp;
}

void ytRsSolenoidDriver::Set(uint8_t num,uint8_t status){
    TxBuf[num] = status;
}

void ytRsSolenoidDriver::Update(){
    uint8_t temp = Convert();
    dev.Write(DevID,&temp,1);
}