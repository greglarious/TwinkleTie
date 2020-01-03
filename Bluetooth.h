#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

//
// simple bluetooth helper
//
#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLE_READPACKET_TIMEOUT         3     // Timeout in ms waiting to read a response

#define BLUEFRUIT_UART_RTS_PIN         -1    // Optional, set to -1 if unused
#define BLUEFRUIT_UART_MODE_PIN        12    // Set to -1 if unused

#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4     // Optional but recommended, set to -1 if unused

#define BLUEFRUIT_SPI_SCK              13
#define BLUEFRUIT_SPI_MISO             12
#define BLUEFRUIT_SPI_MOSI             11
#define FACTORYRESET_ENABLE            1
#define MODE_LED_BEHAVIOUR             "MODE"

#define PACKET_BUTTON_LEN              5
#define PACKET_COLOR_LEN               6

#define READ_BUFSIZE                   20

Adafruit_BluefruitLE_SPI bluefruit(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
uint8_t packet_buffer[READ_BUFSIZE+1];

uint8_t readBluetoothPacket() {
  uint16_t timeout_millis = BLE_READPACKET_TIMEOUT;
  uint16_t time_remaining = timeout_millis;
  uint16_t reply_bytes = 0;

  memset(packet_buffer, 0, READ_BUFSIZE);

  while (time_remaining--) {
    if (reply_bytes >= 20) break;
    if ((packet_buffer[1] == 'B') && (reply_bytes == PACKET_BUTTON_LEN))
      break;
    if ((packet_buffer[1] == 'C') && (reply_bytes == PACKET_COLOR_LEN))
      break;

    while (bluefruit.available()) {
      char c =  bluefruit.read();
      if (c == '!') {
        reply_bytes = 0;
      }
      packet_buffer[reply_bytes] = c;
      reply_bytes++;
      time_remaining = timeout_millis;
    }
    
    if (time_remaining == 0) break;
    delay(1);
  }

  packet_buffer[reply_bytes] = 0;  // null term

  if (!reply_bytes)  // no data or timeout 
    return 0;
  if (packet_buffer[0] != '!')  // doesn't start with '!' packet beginning
    return 0;
  
  // check checksum!
  uint8_t sent_checksum = 0;
  uint8_t recv_checksum = packet_buffer[reply_bytes-1];
  
  for (uint8_t i=0; i<reply_bytes-1; i++) {
    sent_checksum += packet_buffer[i];
  }
  sent_checksum = ~sent_checksum;

  if (sent_checksum != recv_checksum)
  {
    return 0;
  }
  
  return reply_bytes;
}

void bluetoothSetup(void) {
  bluefruit.begin(false);
  bluefruit.factoryReset();
  bluefruit.echo(false);
  while (! bluefruit.isConnected()) {
    delay(500);
  }
  bluefruit.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  bluefruit.setMode(BLUEFRUIT_MODE_DATA);
}
