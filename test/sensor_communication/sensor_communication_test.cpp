#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "sensor_communication.h"
#include "sensor_uart.h"

#include "sensor_uart_mock.h"

using ::testing::AtLeast;
using ::testing::ElementsAreArray;
using ::testing::Return;

TEST(ReadDataTest, succeed) {
  sensor_communication::SensorUartMock* sensor_uart_mock =
      new sensor_communication::SensorUartMock;
  auto expectedCommand = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  EXPECT_CALL(*sensor_uart_mock, SendBytes(ElementsAreArray(expectedCommand)))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));
  std::vector<uint8_t> return_data = {0xFF, 0x86, 0x01, 0x90, 0x00,
                                      0x00, 0x00, 0x00, 0xE9};
  EXPECT_CALL(*sensor_uart_mock, RecvBytes())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_data));

  sensor_communication::SensorCommunication sensor(sensor_uart_mock);

  auto actual_data = sensor.ReadData();
  EXPECT_EQ(400, actual_data);
}

TEST(ReadDataTest, failed_with_invalid_check_command) {
  sensor_communication::SensorUartMock* sensor_uart_mock =
      new sensor_communication::SensorUartMock;
  auto expectedCommand = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  EXPECT_CALL(*sensor_uart_mock, SendBytes(ElementsAreArray(expectedCommand)))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));
  std::vector<uint8_t> return_data = {0xFF, 0xFF, 0x01, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x01};
  EXPECT_CALL(*sensor_uart_mock, RecvBytes())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_data));

  sensor_communication::SensorCommunication sensor(sensor_uart_mock);

  auto actual_data = sensor.ReadData();
  EXPECT_EQ(-1, actual_data);
}

TEST(ReadDataTest, failed_with_invalid_check_sum) {
  sensor_communication::SensorUartMock* sensor_uart_mock =
      new sensor_communication::SensorUartMock;
  auto expectedCommand = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  EXPECT_CALL(*sensor_uart_mock, SendBytes(ElementsAreArray(expectedCommand)))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));
  std::vector<uint8_t> return_data = {0xFF, 0x86, 0x01, 0x90, 0x00,
                                      0x00, 0x00, 0x00, 0xFF};
  EXPECT_CALL(*sensor_uart_mock, RecvBytes())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(return_data));

  sensor_communication::SensorCommunication sensor(sensor_uart_mock);

  auto actual_data = sensor.ReadData();
  EXPECT_EQ(-1, actual_data);
}