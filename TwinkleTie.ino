#define ARDUINO_SAMD_ZERO

#include <FastLED.h>

int cIntensity = 95;
const int NUM_LEDS = 144;
const int patternLength = 10000;
const int BRIGHTNESS = 255;
const int MIN_BRIGHTNESS = 50;
const int MAX_BRIGHTNESS = 250;

const uint16_t top_right = NUM_LEDS / 2 - 1;
const uint16_t bottom_right = 0;
const uint16_t top_left = NUM_LEDS / 2;
const uint16_t bottom_left = NUM_LEDS - 1;

CRGB leds[NUM_LEDS];

CRGB cBlack = CRGB(0, 0, 0);
CRGB cWarmWhite = CRGB(cIntensity, cIntensity / 1.2, cIntensity / 3.4);
CRGB cWhite = CRGB(cIntensity, cIntensity, cIntensity);
CRGB cGreen = CRGB(0, cIntensity, 0);
CRGB cRed = CRGB(cIntensity, 0, 0);
CRGB cBlue = CRGB(0, 0, cIntensity);

long patternEnd = 0;
int curPatternNum = 0;

#define NO_PATTERN 0
#define SPARKLE_PATTERN 1
#define ICICLE_PATTERN 2
#define CANDY_CANE_PATTERN 3
#define CIRCLE_CANE_PATTERN 4

#include "Twinkler.h" 
#include "icicle.h"
#include "Fader.h"
#include "TwinklePatterns.h"
#include "sparkler.h"
#include "bluetooth.h"

void setup() {
  bluetoothSetup();
  Serial.begin(115200);
  FastLED.addLeds<WS2811, A1, GRB>(leds, 0, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  eraseTree();  
}

void updateColors() {
  cWarmWhite = CRGB(cIntensity, cIntensity / 1.2, cIntensity / 3.4);
  cWhite = CRGB(cIntensity, cIntensity, cIntensity);
  cGreen = CRGB(0, cIntensity, 0);
  cRed = CRGB(cIntensity, 0, 0);
  cBlue = CRGB(0, 0, cIntensity);
}

void increaseBrightness() {
  if (cIntensity < MAX_BRIGHTNESS) cIntensity += 5;
  updateColors();
}

void decreaseBrightness() {
  if (cIntensity > MIN_BRIGHTNESS) cIntensity -= 5;
  updateColors();
}

void runPattern() {
  if (curPatternNum != NO_PATTERN && millis() >= patternEnd) {  
    eraseTree();
    curPatternNum = NO_PATTERN;
  }
  
  switch (curPatternNum) {
    case NO_PATTERN:
      break;
    case SPARKLE_PATTERN:
      doSparkler();
      break;
    case ICICLE_PATTERN:
      doIcicle();
      break;
    case CANDY_CANE_PATTERN:
      doCandyCane();
      break;
    case CIRCLE_CANE_PATTERN:
      doCircleCane();
      break;
  }
}

void startPattern(int patternNum) {
  eraseTree();
  curPatternNum = patternNum;
  patternEnd = millis() + patternLength;
}

void loop(void)
{
  runPattern();

  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;
 
  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    switch (buttnum) {
      case 1:
        startPattern(SPARKLE_PATTERN);
        break;
      case 2:
        startPattern(ICICLE_PATTERN);
        break;
      case 3:
        startPattern(CANDY_CANE_PATTERN);
        break;
      case 4:
        startPattern(CIRCLE_CANE_PATTERN);
        break;
      case 5:
        increaseBrightness();
        break;
      case 6:
        decreaseBrightness();
        break; 
    }
  }
  else if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    for (int i=0; i < NUM_LEDS; i++) {
      leds[i].r = red;
      leds[i].g = green;
      leds[i].b = blue;
    }
    FastLED.show();
  }
}
void oldloop() {

  //
  // retro color twinkle
  //  
  eraseTree();
  setRetroTwinkle();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    loopTwinkler(); 
  }  

  // pulse red and green
  patternEnd = millis() + patternLength;
  eraseTree();
  while (millis() < patternEnd) {  
    colorPulses();
  }
  
  //
  // christmas color twinkle 
  //  
  eraseTree();
  setupRainbowTwinkle();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    loopTwinkler(); 
  }  

  // red green up down wipes
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    colorWipes();
  }
  
  // 
  // classic white twinkle
  //
  eraseTree();
  setClassicWhiteTwinkle();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    loopTwinkler(); 
  }
}
