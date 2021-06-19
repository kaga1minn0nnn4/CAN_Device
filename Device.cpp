#include "Device.hpp"

namespace CAN_Device_Lib{

    void CAN_Device::Setup(void(*RxHandle)(void*)){
        can.begin(CAN_STDID,CAN_1000KBPS,MCP_20MHZ);
        pinMode(RxInt,INPUT);
        can.setMode(MCP_NORMAL);
        xTaskCreatePinnedToCore(RxHandle,"CAN_Rx_Task",4096,NULL,1,&th,0);
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

    void CAN_Device::Read(long unsigned int* id,std::vector<uint8_t>& buf){
        uint8_t tempBuf[8];
        uint8_t len;
        can.readMsgBuf(id,&len,tempBuf);
        for(int i = 0;i < len;i++){
            buf.push_back(tempBuf[i]);
        }
    }
}
