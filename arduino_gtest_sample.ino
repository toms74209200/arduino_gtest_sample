/**
 * @file arduino_gtest_sample.ino
 * @brief Arduino GoogleTest actual code
 * GoogleTest sample test code are in test directory.
 *
 * Copyright (c) 2022 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "src/host_communication/host_communication.h"
#include "src/impl/host_uart_impl.h"
#include "src/impl/sensor_uart_impl.h"
#include "src/sensor_communication/sensor_communication.h"

constexpr uint16_t HOST_BAUDRATE = 9600;
constexpr uint16_t SENSOR_BAUDRATE = 9600;
constexpr uint8_t SENSOR_RX_PIN = 1;
constexpr uint8_t SENSOR_TX_PIN = 0;

host_communication::HostUartImpl host_uart(HOST_BAUDRATE);
host_communication::HostCommunication host(&host_uart);
sensor_communication::SensorUartImpl sensor_uart;
sensor_communication::SensorCommunication sensor;

void setup() {
  sensor_uart = sensor_communication::SensorUartImpl::Builder()
                    .RxPin(SENSOR_RX_PIN)
                    ->TxPin(SENSOR_TX_PIN)
                    ->BaudRate(SENSOR_BAUDRATE)
                    ->Build();
  sensor = sensor_communication::SensorCommunication(&sensor_uart);
}

void loop() {
  if (host.RecvGetCommand()) {
    auto data = sensor.ReadData();
    if (data > 0) {
      host.SendString(std::to_string(data) + "\n");
    }
  }
}
