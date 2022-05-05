#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <vector>

namespace CAN_Device_Lib{

    namespace Device{
        typedef union{
            int16_t data;
            uint8_t buf[2];
        }byte2_convert_t;
    }

    class CAN_Device{
        MCP_CAN can_;
        uint8_t rx_int_;
        TaskHandle_t th_;
    public:
        CAN_Device(uint8_t ss = 32,uint8_t rx_int = 33):can_{ss},rx_int_{rx_int}{}
        void Setup(void(*rx_handler)(void* arg));
        void Setup();
        void Write(uint16_t id,std::vector<uint8_t> tx_buf);
        void Write(uint16_t id,uint8_t* tx_buf,uint8_t len);
        
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