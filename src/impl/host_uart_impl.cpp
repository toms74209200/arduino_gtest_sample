/**
 * @file host_uart_impl.cpp
 * @brief Host UART implementation
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "host_uart_impl.h"

host_communication::HostUartImpl::HostUartImpl() {}

host_communication::HostUartImpl::HostUartImpl(const uint16_t baudrate) {
  Serial.begin(baudrate);
}

std::vector<uint8_t> host_communication::HostUartImpl::RecvData() {
  auto recv_byte = std::vector<uint8_t>();
  while (Serial.available()) {
    int8_t data = Serial.read();
    if (data == -1) {
      return {};
    }
    recv_byte.push_back(data);
  }
  return recv_byte;
}

bool host_communication::HostUartImpl::SendString(const std::string data) {
  Serial.print(data.c_str());
  return true;
}
