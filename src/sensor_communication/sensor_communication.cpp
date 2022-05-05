/**
 * @file sensor_communication.cpp
 * @brief Sensor communication
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include <algorithm>

#include "sensor_communication.h"

const uint8_t sensor_communication::Constants::kStartByte = 0xFF;
const uint8_t sensor_communication::Constants::kRequestSensor = 0x01;
const uint8_t sensor_communication::Constants::kResponceSensor = 0x86;
const uint8_t sensor_communication::Constants::kReadCo2 = 0x86;
const uint8_t sensor_communication::Constants::kCommandLength = 9;

sensor_communication::SensorCommunication::SensorCommunication(){};

sensor_communication::SensorCommunication::SensorCommunication(
    sensor_communication::SensorUart* sensor_uart) {
  this->sensor_uart_ = sensor_uart;
}

int32_t sensor_communication::SensorCommunication::ReadData() {
  std::vector<uint8_t> request_command = {Constants::kStartByte,
                                          Constants::kRequestSensor,
                                          Constants::kReadCo2,
                                          0x00,
                                          0x00,
                                          0x00,
                                          0x00,
                                          0x00};
  auto check_sum = CalcCheckSum(request_command);
  request_command.push_back(check_sum);
  this->sensor_uart_->SendBytes(request_command);
  auto data = RecvData();
  if (data[1] != Constants::kResponceSensor) {
    return -1;
  }
  std::vector<uint8_t> check_sum_vector(Constants::kCommandLength - 1);
  std::copy(data.begin(), data.end() - 1, check_sum_vector.begin());
  if (data[Constants::kCommandLength - 1] != CalcCheckSum(check_sum_vector)) {
    return -1;
  }
  return (data[2] << 8) + data[3];
}

std::vector<uint8_t> sensor_communication::SensorCommunication::RecvData() {
  auto data = this->sensor_uart_->RecvBytes();
  std::vector<uint8_t> result(Constants::kCommandLength);
  for (auto itr = data.begin(); itr != data.end(); ++itr) {
    if (*itr == Constants::kStartByte) {
      std::copy(itr, itr + Constants::kCommandLength, result.begin());
      return result;
    }
  }
  return result;
}

uint8_t sensor_communication::SensorCommunication::CalcCheckSum(
    const std::vector<uint8_t> data) {
  uint8_t check_sum = 0;
  for (auto i : data) {
    check_sum += i;
  }
  check_sum = 0xff - check_sum;
  return check_sum;
}