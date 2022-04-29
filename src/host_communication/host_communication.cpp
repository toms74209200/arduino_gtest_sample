/**
 * @file host_communication.cpp
 * @brief Host communication
 */

#include "host_communication.h"

const uint8_t host_communication::Constants::kGetCommand[] = {0x67, 0x65, 0x74,
                                                              0x0d};
const uint8_t host_communication::Constants::kGetCommandLength =
    sizeof(host_communication::Constants::kGetCommand) / sizeof(uint8_t);

host_communication::HostCommunication::HostCommunication(
    host_communication::HostUart* host_uart) {
  this->host_uart_ = host_uart;
}

bool host_communication::HostCommunication::RecvGetCommand() {
  auto data = this->host_uart_->RecvData();
  if (data.empty()) {
    return false;
  }
  uint8_t data_size = data.size();
  if (data_size < host_communication::Constants::kGetCommandLength) {
    return false;
  }
  for (uint8_t i = 0;
       i < data_size - host_communication::Constants::kGetCommandLength + 1;
       i++) {
    if (data[i] == host_communication::Constants::kGetCommand[0] &&
        data[i + 1] == host_communication::Constants::kGetCommand[1] &&
        data[i + 2] == host_communication::Constants::kGetCommand[2] &&
        data[i + 3] == host_communication::Constants::kGetCommand[3]) {
      return true;
    }
  }
  return false;
}

bool host_communication::HostCommunication::SendString(const std::string data) {
  return this->host_uart_->SendString(data);
}