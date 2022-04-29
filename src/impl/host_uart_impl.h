/**
 * @file host_uart_impl.h
 * @brief Host UART implementation
 */

#pragma once

#include <Arduino.h>

#include "../host_communication/host_uart.h"

namespace host_communication {
class HostUartImpl : public HostUart {
 public:
  HostUartImpl();
  /**
   * constractor
   * @param[in] baudrate Serial baudrate
   */
  HostUartImpl(const uint16_t baudrate);
  std::vector<uint8_t> RecvData();
  bool SendString(const std::string data);
};

}  // namespace host_communication