/**
 * @file sensor_uart.h
 * @brief Sensor UART
 */

#pragma once

#include <cstdint>
#include <vector>

namespace sensor_communication {
class SensorUart {
 public:
  virtual ~SensorUart(){};
  /**
   * returns received data
   * @return Receiving data.
   * Returns empty vector if it failed to receive.
   */
  virtual std::vector<uint8_t> RecvBytes() = 0;

  /**
   * sends data bytes
   * @param[in] Send data
   * @return Sending result
   * Returns true if it is succeeded
   */
  virtual bool SendBytes(std::vector<uint8_t> data) = 0;
};
}  // namespace sensor_communication
