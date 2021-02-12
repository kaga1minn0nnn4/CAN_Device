#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

namespace CAN_Device_Lib{

    class CAN_Device{
        MCP_CAN can;
        uint8_t RxInt;
        TaskHandle_t th;
    public:
        CAN_Device(uint8_t ss = 32,uint8_t RxInt = 33):can{ss},RxInt{RxInt}{}
        void Setup(void(*RxHandle)(void* arg));
        void Setup();
        void Write(uint16_t id,std::vector<uint8_t> TxBuf);
        void Write(uint16_t id,uint8_t* TxBuf,uint8_t len);
        
        void Read(long unsigned int* id,std::vector<uint8_t>& buf);
    };

}

/*
void CAN_Device_RxHandler(void* pvParameters){
  while(1){
    if(!digitalRead(33)){
      unsigned long int id;
      std::vector<uint8_t> data;
      dev.Read(&id,data);
      
      if(id == md.ReadID()){
        md.RxHandler(data[0]);
        printf("%d\n",data[0]);
      }
    }
    vTaskDelay(1);
  }
}
*/

#endif