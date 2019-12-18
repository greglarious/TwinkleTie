#include "ColorPalette.h"

#define MAX_TWINKLERS 50

class Twinkler {
  static byte usedPositions[];
  static byte numTwinklers;
  static float maxVal;
  static float minVal;
  static float increment;
  static byte delayMax; 
  static byte numLeds;
  static ColorPalette *palette;

  byte twinklerIndex;
  byte startupDelay;
  byte index;
  float value;
  
  boolean up;

  CRGB color;
  
public:
  static void setup(int numTwinklersValue, int numLedsValue, float minValue, float maxValue, float incrementValue, int delayValue, ColorPalette *pal );

  
  Twinkler();
  void initialize(int twinklerIndexValue );  
  void doTwinkle();
  void setInto(CRGB leds[]);  
  
private:
  CRGB getValue();
  boolean checkUsed(int pos);
  void randomize();  
};
