#include <Arduino.h>
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device dev{};
CAN_Device_Lib::Device::MD_Base md{dev,0};

void setup() {
  // put your setup code here, to run once:
  dev.Setup();
  md.SetEncoderResolution(57);
}

void loop() {
  // put your main code here, to run repeatedly:
  md.MoveDuty(0,512,0);
  //md.MoveDistance(2,57 * 10,1);
  md.MoveRpm(2,200,1);
  md.Update();
}