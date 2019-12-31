#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLE_READPACKET_TIMEOUT         20   // Timeout in ms waiting to read a response

#define BLUEFRUIT_UART_RTS_PIN         -1   // Optional, set to -1 if unused
#define BLUEFRUIT_UART_MODE_PIN        12    // Set to -1 if unused

#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused

#define BLUEFRUIT_SPI_SCK              13
#define BLUEFRUIT_SPI_MISO             12
#define BLUEFRUIT_SPI_MOSI             11
#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);

extern uint8_t packetbuffer[];

void bluetoothSetup(void)
{
  ble.begin(false);
  ble.factoryReset();
  ble.echo(false);
  while (! ble.isConnected()) {
      delay(500);
  }

  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }
  ble.setMode(BLUEFRUIT_MODE_DATA);
}
