/**
 * @file sensor_uart_impl.cpp
 * @brief Sensor UART implementation
 */

#include "sensor_uart_impl.h"

sensor_communication::SensorUartImpl::SensorUartImpl(){};

sensor_communication::SensorUartImpl::SensorUartImpl(
    sensor_communication::SensorUartImpl::Builder builder) {
  this->rx_pin_ = builder.rx_;
  this->tx_pin_ = builder.tx_;
  this->baudrate_ = builder.baudrate_;
  Serial1.setRX(this->rx_pin_);
  Serial1.setTX(this->tx_pin_);
  Serial1.begin(this->baudrate_);
}

std::vector<uint8_t> sensor_communication::SensorUartImpl::RecvBytes() {
  std::vector<uint8_t> buffer(10);
  while (Serial1.available() > 0) {
    buffer.push_back(Serial1.read());
  }
  return buffer;
}

bool sensor_communication::SensorUartImpl::SendBytes(
    std::vector<uint8_t> data) {
  for (auto i : data) {
    Serial1.write(i);
  }
  return true;
}