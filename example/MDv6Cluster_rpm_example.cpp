#include <Arduino.h>
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device dev{};
CAN_Device_Lib::Device::MDv6Cluster md{dev, 15};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dev.Setup();
  md.ResetDeviceAll();
  md.SetEncoderDirection(3, 1);
  md.SetEncoderResolutionAll(57);
}

void loop() {
  // put your main code here, to run repeatedly:
  md.MoveWithRpm(3,1.0);
  md.Update();
}
