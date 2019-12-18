#include <FastLED.h>
#include "Twinkler.h"

byte Twinkler::numTwinklers = 0;
byte  Twinkler::usedPositions[MAX_TWINKLERS];
float Twinkler::maxVal;
float Twinkler::minVal;
float Twinkler::increment;
byte Twinkler::delayMax; 
byte Twinkler::numLeds;
ColorPalette *Twinkler::palette;
Twinkler::Twinkler() {
}

void Twinkler::setup(int numTwinklersValue, int numLedsValue, float minValue, float maxValue, float incrementValue, int delayValue, ColorPalette *pal ) {
  numTwinklers = numTwinklersValue;
  numLeds = numLedsValue;
  minVal = minValue;
  maxVal = maxValue;
  increment = incrementValue;
  delayMax = delayValue;
  palette = pal;
}
   
void Twinkler::initialize(int twinklerIndexValue) {
  twinklerIndex = twinklerIndexValue;
  usedPositions[twinklerIndex] = -1;

  value = 0;
  up = true;

}
  
boolean Twinkler::checkUsed(int pos) {
  for (int i=0; i < numTwinklers; i++) {
    if (usedPositions[i] == pos) {
      return true;
    }
  }
  return false;
}

void Twinkler::randomize() {
  startupDelay = random(delayMax);
  do {
    index = random(numLeds);
  } while (checkUsed(index));
  usedPositions[twinklerIndex] = index;
  
  color = palette->getRandom();
}
    
void Twinkler::setInto(CRGB leds[]) {
  if (startupDelay == 0) {
    leds[index] = getValue();
  }
}
  
void Twinkler::doTwinkle() {
  if (startupDelay > 0) {
    startupDelay--;
    return;
  }
  
  if (up) {
    if (value == minVal) {
      randomize();
    }
    if (value < maxVal) {
      value += increment;
      if (value > maxVal) value = maxVal;
    } else {
      up = false;
    }
  } else {
    if (value > minVal) {
      value-= increment;
      if (value < minVal) value = minVal;
    } else {
      up = true;
    }
  }
}
  
CRGB Twinkler::getValue() {
  CRGB rval;
  

  rval.r = (float)color.r * value;
  rval.g = (float)color.g * value;
  rval.b = (float)color.b * value;
  return rval;
}
