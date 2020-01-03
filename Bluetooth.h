#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

//
// simplified bluetooth helpers inspired by the Adafruit example and reduced to minimum needed items
//

#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLE_READPACKET_TIMEOUT         3   // Timeout in ms waiting to read a response

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

#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)

#define READ_BUFSIZE                    (20)

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
uint8_t packet_buffer[READ_BUFSIZE+1];

uint8_t readBluetoothPacket() {
  uint16_t timeout = BLE_READPACKET_TIMEOUT;
  uint16_t origtimeout = timeout, replyidx = 0;

  memset(packet_buffer, 0, READ_BUFSIZE);

  while (timeout--) {
    if (replyidx >= 20) break;
    if ((packet_buffer[1] == 'B') && (replyidx == PACKET_BUTTON_LEN))
      break;
    if ((packet_buffer[1] == 'C') && (replyidx == PACKET_COLOR_LEN))
      break;

    while (ble.available()) {
      char c =  ble.read();
      if (c == '!') {
        replyidx = 0;
      }
      packet_buffer[replyidx] = c;
      replyidx++;
      timeout = origtimeout;
    }
    
    if (timeout == 0) break;
    delay(1);
  }

  packet_buffer[replyidx] = 0;  // null term

  if (!replyidx)  // no data or timeout 
    return 0;
  if (packet_buffer[0] != '!')  // doesn't start with '!' packet beginning
    return 0;
  
  // check checksum!
  uint8_t xsum = 0;
  uint8_t checksum = packet_buffer[replyidx-1];
  
  for (uint8_t i=0; i<replyidx-1; i++) {
    xsum += packet_buffer[i];
  }
  xsum = ~xsum;

  // Throw an error message if the checksum's don't match
  if (xsum != checksum)
  {
    Serial.print("Checksum mismatch in packet : ");
    return 0;
  }
  
  // checksum passed!
  return replyidx;
}

void bluetoothSetup(void) {
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
