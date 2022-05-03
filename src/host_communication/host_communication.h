/**
 * @file host_communication.h
 * @brief Host communication
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <string>

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

  /**
   * sends string data
   * @param[in] Send data
   * @return Sending result
   * Returns true if it is succeeded
   */
  bool SendString(const std::string data);

 private:
  HostUart* host_uart_;
};
}  // namespace host_communication