/**
 * @file sensor_communication.h
 * @brief Sensor communication
 */

#pragma once

#include <cstdint>

#include "sensor_uart.h"

namespace sensor_communication {

struct Constants {
  static const uint8_t START_BYTE;
  static const uint8_t REQUEST_SENSOR;
  static const uint8_t RESPONCE_SENSOR;
  static const uint8_t READ_CO2;
  static const uint8_t COMMAND_LENGTH;
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