/**
 * @file host_communication.h
 * @brief Host communication
 */

#pragma once

#include "host_uart.h"

namespace host_communication {

struct Constants {
  static const uint8_t kGetCommand[];
  static const uint8_t kGetCommandLength;
};

class HostCommunication {
 public:
  /**
   * Constractor
   * @param[in] host_uart UART module
   */
  HostCommunication(HostUart* host_uart);

  /**
   * returns received command result
   * @return Result of receiving command.
   * Returns true if it receive "get" command,
   * and returns false if any others
   */
  bool RecvGetCommand();

 private:
  HostUart* host_uart_;
};
}  // namespace host_communication