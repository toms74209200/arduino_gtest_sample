/**
 * @file sensor_uart_impl.h
 * @brief sensor UART implementation
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <Arduino.h>

#include "../sensor_communication/sensor_uart.h"

namespace sensor_communication {

class SensorUartImpl : public SensorUart {
 public:
  class Builder {
   public:
    /**
     * Builder constractor.
     * example;
     * @code{.cpp}
     * SensorUartImpl sensor_uart = SensorUartImpl::Builder()
     *   .RxPin(1)
     *   ->TxPin(0)
     *   ->BaudRate(9600)
     *   ->Build();
     * @endcode
     */
    Builder(){};
    ~Builder(){};
    Builder* RxPin(uint8_t rx) {
      this->rx_ = rx;
      return this;
    };
    Builder* TxPin(uint8_t tx) {
      this->tx_ = tx;
      return this;
    };
    Builder* BaudRate(uint16_t baudrate) {
      this->baudrate_ = baudrate;
      return this;
    };
    SensorUartImpl Build() {
      return sensor_communication::SensorUartImpl(*this);
    }

    uint8_t rx_;
    uint8_t tx_;
    uint16_t baudrate_;
  };
  SensorUartImpl();
  std::vector<uint8_t> RecvBytes();
  bool SendBytes(std::vector<uint8_t> data);

 private:
  SensorUartImpl(Builder builder);

  uint8_t rx_pin_;
  uint8_t tx_pin_;
  uint16_t baudrate_;
};

}  // namespace sensor_communication
