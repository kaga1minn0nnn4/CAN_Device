#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

class CAN_Device{
    MCP_CAN can;
    uint8_t RxInt;
public:
    CAN_Device(uint8_t ss = 32,uint8_t RxInt = 33):can{ss},RxInt{RxInt}{}
    void Setup(void(*RxHandle)(void));
    void Setup();
    void Write(uint16_t id,std::vector<uint8_t> TxBuf);
    void Write(uint16_t id,uint8_t* TxBuf,uint8_t len);
};

#endif