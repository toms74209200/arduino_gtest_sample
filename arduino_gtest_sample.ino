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

constexpr uint16_t kHostBaudrate = 9600;
constexpr uint16_t kSensorBaudrate = 9600;
constexpr uint8_t kSensorRxPin = 1;
constexpr uint8_t kSensorTxPin = 0;

host_communication::HostUartImpl host_uart(kHostBaudrate);
host_communication::HostCommunication host(&host_uart);
sensor_communication::SensorUartImpl sensor_uart;
sensor_communication::SensorCommunication sensor;

void setup() {
  sensor_uart = sensor_communication::SensorUartImpl::Builder()
                    .RxPin(kSensorRxPin)
                    ->TxPin(kSensorTxPin)
                    ->BaudRate(kSensorBaudrate)
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
