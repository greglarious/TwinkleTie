#define ARDUINO_SAMD_ZERO

#include <FastLED.h>

#include "Twinkler.h" 

const int cIntensity = 45;
const int iIntensity = 110;
const int NUM_LEDS = 144;
const int BRIGHTNESS = 100;
const int cane_size = 10;
const int patternLength = 6000;

const uint16_t top_right = NUM_LEDS / 2 - 1;
const uint16_t bottom_right = 0;
const uint16_t top_left = NUM_LEDS / 2;
const uint16_t bottom_left = NUM_LEDS - 1;

CRGB leds[NUM_LEDS];

const CRGB cBlack = CRGB(0, 0, 0);
const CRGB cWarmWhite = CRGB(cIntensity, cIntensity / 1.2, cIntensity / 3.4);
const CRGB cWhite = CRGB(cIntensity, cIntensity, cIntensity);
const CRGB cGreen = CRGB(0, cIntensity, 0);
const CRGB cRed = CRGB(cIntensity, 0, 0);
const CRGB cBlue = CRGB(0, 0, cIntensity);

#include "icicle.h"
#include "fader.h"
#include "TwinklePatterns.h"

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2811, A3, GRB>(leds, 0, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  eraseTree();  
}

void loop() {
  long patternEnd = 0;

  // circling blue white stripes
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    circleCane();
  }
  
  // falling icicle
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    fallingIcicle();
  }

  // 
  // sparkler
  //
  const int numSparkle = 30;
  int curIndex[numSparkle];
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    for (int i=0; i<numSparkle; i++) curIndex[i] = random(NUM_LEDS);
    for (int i=0; i<numSparkle; i++) leds[curIndex[i]] = cWarmWhite;
    FastLED.show(); 
    for (int i=0; i<numSparkle; i++) leds[curIndex[i]] = cBlack;
    delay(40);
  }
  // falling candycane stripes
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    candyCane();
  }
  
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
