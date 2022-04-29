#include "src/host_communication/host_communication.h"
#include "src/impl/host_uart_impl.h"

constexpr uint16_t BAUDRATE = 9600;
host_communication::HostUartImpl host_uart(BAUDRATE);
host_communication::HostCommunication host(&host_uart);

void setup() {}

void loop() {
  if (host.RecvGetCommand()) {
    std::string data("recieved\n");
    host.SendString(data);
  }
}
