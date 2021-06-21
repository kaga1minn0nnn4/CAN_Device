#ifndef PURE_TOF_H
#define PURE_TOF_H

#include "Device.hpp"

namespace CAN_Device_Lib{
  
  namespace Device{

    typedef union{
        int16_t data;
        uint8_t buf[2];
    }byte2_convert_t;


    class PureToF{
        CAN_Device& dev;
        uint16_t DevID;

        byte2_convert_t ranging;
    public:
        PureToF(CAN_Device& dev,uint16_t id):dev{dev},DevID{id}{}
        void RxHandler(std::vector<uint8_t> data);

        uint16_t ReadID()const;

        int16_t ReadRangingData()const;
    };

  }

}

#endif