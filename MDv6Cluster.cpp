#include "MDv6Cluster.hpp"

namespace CAN_Device_Lib{
  namespace Device{
    void MDv6Cluster::ResetDevice(uint8_t md_num){
      txbuf_update(md_num, move_type_t::reset, 0, 0);
    }

    void MDv6Cluster::ResetDeviceAll(){
      for(int i = 0;i < 4;i++){
        ResetDevice(i);
      }
      Update();
    }

    void MDv6Cluster::SetEncoderResolution(uint8_t md_num, uint16_t resolution){
      enc_res_[md_num] = resolution;
    }

    void MDv6Cluster::SetEncoderResolutionAll(uint16_t resolution){
      for(int i = 0;i < 4;i++){
        SetEncoderResolution(i, resolution);
      }
    }

    void MDv6Cluster::SetEncoderDirection(uint8_t md_num, uint8_t value){
      enc_dir_[md_num] = value;
    }

    void MDv6Cluster::MoveWithDuty(uint8_t md_num, int16_t value){
      uint8_t sign = static_cast<uint8_t>(value > 0);
      uint16_t value_abs = abs(value);
      if(value_abs > kPwmValueMax){
        value_abs = kPwmValueMax;
      }
      txbuf_update(md_num, move_type_t::duty, sign, value_abs);
    }

    void MDv6Cluster::MoveWithRpm(uint8_t md_num, double rpm){
      double rotation_per_T = rpm / 60.0 * kEncoderSamplingPeriod;
      double value = rotation_per_T * enc_res_[md_num];

      uint8_t sign = static_cast<uint8_t>(value > 0);
      uint16_t value_abs = static_cast<uint16_t>(abs(value));
      
      txbuf_update(md_num, move_type_t::speed, sign, value_abs);
      printf("%d\n",value_abs);
    }

    void MDv6Cluster::Update(){
      dev_.Write(dev_id_, tx_buffer_.buf, 8);
    }
  }
}