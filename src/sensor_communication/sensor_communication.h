/**
 * @file sensor_communication.h
 * @brief Sensor communication
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <cstdint>

#include "sensor_uart.h"

namespace sensor_communication {

struct Constants {
  static const uint8_t kStartByte;
  static const uint8_t kRequestSensor;
  static const uint8_t kResponceSensor;
  static const uint8_t kReadCo2;
  static const uint8_t kCommandLength;
};

class SensorCommunication {
 public:
  SensorCommunication();
  /**
   * Constractor
   * @param[in] sensor_uart UART module
   */
  SensorCommunication(SensorUart* sensor_uart);

  /**
   * reads sensor data
   * @return Sensor data.
   * Returns a negative value if it is failed to read a sensor
   */
  int32_t ReadData();

 private:
  SensorUart* sensor_uart_;
  std::vector<uint8_t> RecvData();
  uint8_t CalcCheckSum(const std::vector<uint8_t> data);
};
}  // namespace sensor_communication