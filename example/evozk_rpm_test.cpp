#include <Arduino.h>
#include "CAN_Device.hpp"

CAN_Device_Lib::CAN_Device dev{};
CAN_Device_Lib::Device::Evozk md{dev,0};

int16_t rpm = 200;

void setup() {
  // put your setup code here, to run once:
  dev.Setup();

  md.SetEncoderResolution(57);
  md.SetPidGain(10.0,5.0,0.1);
  md.SetDirection(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  md.MoveRpm(rpm);
}