#define ARDUINO_SAMD_ZERO

#include <FastLED.h>

#include "bluetooth.h"

class TwinkleTie {
public:
  static const int NUM_LEDS = 144;
  static const int BRIGHTNESS = 255;
  
  static const uint16_t top_right = NUM_LEDS / 2 - 1;
  static const uint16_t bottom_right = 0;
  static const uint16_t top_left = NUM_LEDS / 2;
  static const uint16_t bottom_left = NUM_LEDS - 1;
  
  CRGB leds[NUM_LEDS];

  void setupTie() {
    FastLED.addLeds<WS2811, A1, GRB>(leds, 0, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );
  }
};

#include "PatternRunner.h"

TwinkleTie tie;
ColorPalette palette;
PatternRunner patterns(&tie, &palette);

void setup() {
  Serial.begin(115200);
  bluetoothSetup();
  tie.setupTie();
}

void loop(void)
{
  patterns.runLoop();

  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;
 
  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
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
          palette.increaseBrightness();
          break;
        case 6:
          palette.decreaseBrightness();
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
  else if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    for (int i=0; i < tie.NUM_LEDS; i++) {
      tie.leds[i].r = red;
      tie.leds[i].g = green;
      tie.leds[i].b = blue;
    }
    FastLED.show();
  }
}
