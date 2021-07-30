#include "Device.hpp"

namespace CAN_Device_Lib{

    void CAN_Device::Setup(void(*rx_handler)(void*)){
        can_.begin(CAN_STDID,CAN_1000KBPS,MCP_20MHZ);
        pinMode(rx_int_,INPUT);
        can_.setMode(MCP_NORMAL);
        xTaskCreatePinnedToCore(rx_handler,"CAN_Rx_Task",4096,NULL,1,&th_,0);
    }

    void CAN_Device::Setup(){
        can_.begin(CAN_STDID,CAN_1000KBPS,MCP_20MHZ);
        pinMode(rx_int_,INPUT);
        can_.setMode(MCP_NORMAL);
    }

    void CAN_Device::Write(uint16_t id,std::vector<uint8_t> tx_buf){
        uint8_t* temp = &tx_buf[0];
        can_.sendMsgBuf(id,0,tx_buf.size(),temp);
    }

    void CAN_Device::Write(uint16_t id,uint8_t* tx_buf,uint8_t len){
        can_.sendMsgBuf(id,0,len,tx_buf);
    }

    void CAN_Device::Read(long unsigned int* id,std::vector<uint8_t>& buf){
        uint8_t temp_buf[8];
        uint8_t len;
        can_.readMsgBuf(id,&len,temp_buf);
        for(int i = 0;i < len;i++){
            buf.push_back(temp_buf[i]);
        }
    }
}
