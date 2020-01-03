#define ARDUINO_SAMD_ZERO
#include "Bluetooth.h"
#include "PatternRunner.h"

//
// combines bluetooth communication with a pattern runner to make a remote control necktie
//

ShapedLED tie;
PatternRunner patterns(&tie);

void setup() {
  Serial.begin(115200);
  bluetoothSetup();
  tie.setupTie();
  patterns.initPalettes();
}

void loop(void)
{
  patterns.runLoop();

  uint8_t len = readBluetoothPacket();
  if (len == 0) return;
 
  // Buttons
  if (packet_buffer[1] == 'B') {
    uint8_t buttnum = packet_buffer[2] - '0';
    boolean pressed = packet_buffer[3] - '0';
    if (pressed) {
      switch (buttnum) {
        case 1:
          patterns.setMode(MODE_OFF);
          break;
        case 2:
          patterns.setMode(MODE_SOLID);
          break;
        case 3:
          patterns.setMode(MODE_ROLLING);
          break;
        case 4:
          break;
        case 5:
          patterns.increaseBrightness();
          break;
        case 6:
          patterns.decreaseBrightness();
          break;
        case 7:
          patterns.prevPattern();
          break;
        case 8:
          patterns.nextPattern();
          break;
      }
    }
  }
  // Color picker
  else if (packet_buffer[1] == 'C') {
    for (int i=0; i < tie.num_leds; i++) {
      tie.leds[i].r = packet_buffer[2];
      tie.leds[i].g = packet_buffer[3];
      tie.leds[i].b = packet_buffer[4];
    }
    FastLED.show();
  }
}
