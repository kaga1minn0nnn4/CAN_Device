#ifndef YTRS_H
#define YTRS_H

#include "Device.hpp"

class ytRsSolenoidDriver{
    CAN_Device& dev;
    uint16_t DevID;
    uint8_t TxBuf[8];
    uint8_t Convert();
public:
    ytRsSolenoidDriver(CAN_Device& dev,uint16_t id):dev{dev},DevID{id},TxBuf{0,0,0,0,0,0,0,0}{}
    void Set(uint8_t num,uint8_t status);
    void Update();
};

#endif