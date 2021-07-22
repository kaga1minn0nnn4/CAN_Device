#include "Arduino.h"
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device candev{};
CAN_Device_Lib::Device::MD_Base md{candev,0};

void setup(){
    candev.Setup();
}

void loop(){
    md.Move(0,CAN_Device_Lib::Device::MD_Mode_t::DutyMode,1023,true);
}