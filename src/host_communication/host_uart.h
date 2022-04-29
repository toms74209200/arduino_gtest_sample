/**
 * @file host_uart.h
 * @brief Host UART
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace host_communication {
class HostUart {
 public:
  virtual ~HostUart(){};
  /**
   * returns received data
   * @return Receiving data.
   * Returns empty vector if it failed to receive.
   */
  virtual std::vector<uint8_t> RecvData() = 0;

  /**
   * sends string data
   * @param[in] Send data
   * @return Sending result
   * Returns true if it is succeeded
   */
  virtual bool SendString(const std::string s) = 0;
};
}  // namespace host_communication
