#include <FastLED.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#include <hsv2rgb.h>
#include "Twinkler.h"

#define NUM_LEDS    30
#define BRIGHTNESS  40
CRGB leds[NUM_LEDS];

int cIntensity = 250;
CRGB cBlack = CRGB(0, 0, 0);
CRGB cWhite = CRGB(cIntensity, cIntensity, cIntensity);
CRGB cGreen = CRGB(0, cIntensity, 0);
CRGB cRed = CRGB(cIntensity, 0, 0);
CRGB colors[6] = { cRed,cRed,cRed, cWhite, cWhite, cWhite  };

#include "fader.h"
#include "TwinklePatterns.h"

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2811, 7, GRB>(leds, 0, 15);
  FastLED.addLeds<WS2811, 8, GRB>(leds, 15, 15);
  FastLED.setBrightness(  BRIGHTNESS );
  eraseTree();  
}

long patternLength = 10000;

void loop() {
  long patternEnd = 0;

  // falling icicle
  eraseTree();
  patternEnd = millis() + patternLength;
  while (millis() < patternEnd) {  
    fallingIcicle();
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
