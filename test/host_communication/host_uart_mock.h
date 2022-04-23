#pragma once

#include <gmock/gmock.h>

#include "host_uart.h"

namespace host_communication {
class HostUartMock : public HostUart {
 public:
  MOCK_METHOD0(RecvData, std::vector<uint8_t>());
};
}  // namespace host_communication