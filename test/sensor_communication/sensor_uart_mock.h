#pragma once

#include <gmock/gmock.h>

#include "sensor_uart.h"

namespace sensor_communication {
class SensorUartMock : public SensorUart {
  public:
  MOCK_METHOD0(RecvBytes, std::vector<uint8_t>());
  MOCK_METHOD1(SendBytes, bool(std::vector<uint8_t>));
};
}  // namespace sensor_communication