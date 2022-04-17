#include <Arduino.h>
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device dev{};
CAN_Device_Lib::Device::MD_Base md{dev,0};

int16_t rpm = 200;

void setup() {
  // put your setup code here, to run once:
  dev.Setup();

  md.ReverseDir(3,0);
  md.Update();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  md.MoveRpm(2,400,false);
  md.MoveRpm(3,200,false);
  md.Update();
}