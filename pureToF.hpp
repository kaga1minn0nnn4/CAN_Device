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
        CAN_Device& dev_;
        uint16_t dev_id_;

        byte2_convert_t ranging_;
    public:
        PureToF(CAN_Device& dev,uint16_t id):dev_{dev},dev_id_{id}{}
        void RxHandler(std::vector<uint8_t> data);

        uint16_t ReadID()const;

        int16_t ReadRangingData()const;
    };

  }

}

#endif