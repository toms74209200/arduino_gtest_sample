#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "host_communication.h"
#include "host_uart.h"

#include "host_uart_mock.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST(RecvTest, succeed_with_just_data) {
  host_communication::HostUartMock* host_uart_mock =
      new host_communication::HostUartMock;
  auto return_vector = std::vector<uint8_t>{0x67, 0x65, 0x74, 0x0d};
  EXPECT_CALL(*host_uart_mock, RecvData())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_vector));

  host_communication::HostCommunication host(host_uart_mock);
  EXPECT_EQ(true, host.RecvGetCommand());
}

TEST(RecvTest, succeed_with_expanded_data) {
  host_communication::HostUartMock* host_uart_mock =
      new host_communication::HostUartMock;
  auto return_vector =
      std::vector<uint8_t>{0x00, 0x67, 0x65, 0x74, 0x0d, 0x00, 0x00};
  EXPECT_CALL(*host_uart_mock, RecvData())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_vector));

  host_communication::HostCommunication host(host_uart_mock);
  EXPECT_EQ(true, host.RecvGetCommand());
}

TEST(RecvTest, failure_with_empty_data) {
  host_communication::HostUartMock* host_uart_mock =
      new host_communication::HostUartMock;
  auto return_vector = std::vector<uint8_t>{};
  EXPECT_CALL(*host_uart_mock, RecvData())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_vector));

  host_communication::HostCommunication host(host_uart_mock);
  EXPECT_EQ(false, host.RecvGetCommand());
}

TEST(RecvTest, failure_with_short_data) {
  host_communication::HostUartMock* host_uart_mock =
      new host_communication::HostUartMock;
  auto return_vector = std::vector<uint8_t>{0x00, 0x67, 0x65};
  EXPECT_CALL(*host_uart_mock, RecvData())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_vector));

  host_communication::HostCommunication host(host_uart_mock);
  EXPECT_EQ(false, host.RecvGetCommand());
}

TEST(RecvTest, failure_with_invalid_data) {
  host_communication::HostUartMock* host_uart_mock =
      new host_communication::HostUartMock;
  auto return_vector =
      std::vector<uint8_t>{0x00, 0x67, 0x65, 0x00, 0x74, 0x0d, 0x00};
  EXPECT_CALL(*host_uart_mock, RecvData())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_vector));

  host_communication::HostCommunication host(host_uart_mock);
  EXPECT_EQ(false, host.RecvGetCommand());
}