#pragma once

#include "Device.hpp"

namespace CAN_Device_Lib{

  namespace Device{

    class MDv6Cluster{
    private:

      enum class move_type_t{
        duty = 0,
        speed,
        angle,
        reset
      };

      union can_tx_t{
        uint8_t buf[8];
        int16_t value[4];
      };

      static constexpr uint16_t kPwmValueMax = 1023;
      static constexpr double kEncoderSamplingPeriod = 10.0e-3;

      CAN_Device& dev_;
      uint16_t dev_id_;

      can_tx_t tx_buffer_;
      uint8_t enc_dir_[4];
      uint16_t enc_res_[4];

      /*** @brief Update tx_buffer_.*/
      void txbuf_update(uint8_t num, move_type_t cmd, uint8_t sign, uint16_t value){
        tx_buffer_.value[num] = static_cast<uint8_t>(cmd) << 13 |+ enc_dir_[num] << 12 |+ sign << 11 |+ value; 
      }

    public:
      MDv6Cluster(CAN_Device& dev, uint16_t id):dev_{dev}, dev_id_{id}, tx_buffer_{}, enc_dir_{}, enc_res_{}{}

      /*** @brief Reset one device.*/
      void ResetDevice(uint8_t md_num);

      /*** @brief Reset all devices.*/
      void ResetDeviceAll();

      /*** @brief Set one encoder resolution value.*/
      void SetEncoderResolution(uint8_t md_num, uint16_t resolution);

      /*** @brief Set all encoder resolution value.*/
      void SetEncoderResolutionAll(uint16_t resolution);

      /*** @brief Set encoder direction.*/
      void SetEncoderDirection(uint8_t md_num, uint8_t value);

      /*** @brief Move motor with duty.*/
      void MoveWithDuty(uint8_t md_num, int16_t value);

      /*** @brief Move motor with rpm.*/
      void MoveWithRpm(uint8_t md_num, double rpm);

      /*** @brief Send all data to md_base.*/
      void Update();
    };
  }
}