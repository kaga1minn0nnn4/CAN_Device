#include "Device.hpp"

namespace CAN_Device_Lib{

    void CAN_Device::Setup(void(*RxHandle)(void)){
        can.begin(CAN_STDID,CAN_1000KBPS,MCP_20MHZ);
        pinMode(RxInt,INPUT);
        can.setMode(MCP_NORMAL);
        attachInterrupt(RxInt,RxHandle,FALLING);
    }

    void CAN_Device::Setup(){
        can.begin(CAN_STDID,CAN_1000KBPS,MCP_20MHZ);
        pinMode(RxInt,INPUT);
        can.setMode(MCP_NORMAL);
    }

    void CAN_Device::Write(uint16_t id,std::vector<uint8_t> TxBuf){
        uint8_t* temp = &TxBuf[0];
        can.sendMsgBuf(id,0,TxBuf.size(),temp);
    }

    void CAN_Device::Write(uint16_t id,uint8_t* TxBuf,uint8_t len){
        can.sendMsgBuf(id,0,len,TxBuf);
    }

}
