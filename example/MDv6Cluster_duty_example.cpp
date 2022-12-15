#include <Arduino.h>
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device dev{};
CAN_Device_Lib::Device::MDv6Cluster md{dev, 15};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dev.Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  md.MoveWithDuty(3, -512);
  md.Update();
}