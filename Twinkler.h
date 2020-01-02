class ColorPalette {  
  CRGB entries[4];
  byte  numEntries;
  int cIntensity;
  
  void updateColors() {
    cBlack = CRGB(0, 0, 0);
    cWarmWhite = CRGB(cIntensity, cIntensity / 1.2, cIntensity / 3.4);
    cWhite = CRGB(cIntensity, cIntensity, cIntensity);
    cGreen = CRGB(0, cIntensity, 0);
    cRed = CRGB(cIntensity, 0, 0);
    cBlue = CRGB(0, 0, cIntensity);
  }
  
public:
  static const int MIN_BRIGHTNESS = 25;
  static const int MAX_BRIGHTNESS = 210;
  static const int DEFAULT_INTENSITY = 50;
  
  CRGB cBlack;
  CRGB cWarmWhite;
  CRGB cWhite;
  CRGB cGreen;
  CRGB cRed;
  CRGB cBlue;

  ColorPalette (int intensity = DEFAULT_INTENSITY) {
    numEntries = 0;
    cIntensity = intensity;
    updateColors();
  }

  int getIntensity() {
    return cIntensity;
  }
  
  void addColor(CRGB val) {
    float perc = (float)(cIntensity / 255.0) * 2;
    CRGB newcol = CRGB(val.r * perc, val.g * perc, val.b * perc);
    Serial.print("perc:");
    Serial.println(perc);
    entries[numEntries++] = newcol;
  }
  
  CRGB getRandom() {
    return entries[random(numEntries)];
  }

  void increaseBrightness() {
    if (cIntensity < MAX_BRIGHTNESS) cIntensity += 5;
    updateColors();
  }
  
  void decreaseBrightness() {
    if (cIntensity > MIN_BRIGHTNESS) cIntensity -= 5;
    updateColors();
  }
};

class FadeUtils {
public:
  static bool fadeTo(CRGB* leds, byte index, CRGB target, byte increment) { 
    bool fade_completed= true;
    if (leds[index].r < target.r - increment) {
        leds[index].r+= increment;
        fade_completed = false;
    } else if (leds[index].r > target.r + increment) {
        leds[index].r-= increment;
        fade_completed = false;
    } else {
        leds[index].r = target.r;
    }
  
    if (leds[index].g < target.g - increment) {
      leds[index].g+= increment;
      fade_completed = false;
    } else if (leds[index].g > target.g + increment) {
      leds[index].g-= increment;
      fade_completed = false;
    } else {
      leds[index].g = target.g;
    }
  
    if (leds[index].b < target.b - increment) {
      leds[index].b+= increment;
      fade_completed = false;
    } else if (leds[index].b > target.b + increment) {
      leds[index].b-= increment;
      fade_completed = false;
    } else {
      leds[index].b = target.b;
    }
    
    return fade_completed;
  }
  
  static bool fadeAllTo(CRGB* leds, int num_leds, CRGB target, byte increment) {
    bool done = true;
    for(byte idx=0; idx< num_leds; idx++) {
      if(!fadeTo(leds, idx, target, increment)) {
        done = false;
      }
    }
    return done;
  }
};

#define MAX_TWINKLERS 40

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
