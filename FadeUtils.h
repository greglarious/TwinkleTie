//
// utility to work with colors while adusting brightness and organizing into groups
//
class ColorPalette {  
  CRGB entries[4];
  byte  num_entries;
  int intensity;
  
  void updateColors() {
    cBlack = CRGB(0, 0, 0);
    cWarmWhite = CRGB(intensity, intensity / 1.2, intensity / 3.4);
    cWhite = CRGB(intensity, intensity, intensity);
    cGreen = CRGB(0, intensity, 0);
    cRed = CRGB(intensity, 0, 0);
    cBlue = CRGB(0, 0, intensity);
  }
  
public:
  static const int MIN_BRIGHTNESS = 25;
  static const int MAX_BRIGHTNESS = 210;
  static const int DEFAULT_INTENSITY = 45;
  
  CRGB cBlack;
  CRGB cWarmWhite;
  CRGB cWhite;
  CRGB cGreen;
  CRGB cRed;
  CRGB cBlue;

  ColorPalette (int intensity = DEFAULT_INTENSITY) {
    num_entries = 0;
    this->intensity = intensity;
    updateColors();
  }

  int getIntensity() {
    return intensity;
  }

  void clearPalette() {
    num_entries = 0;
  }
  void addColor(CRGB val) {
    float perc = (float)(intensity / 255.0) * 2;
    CRGB newcol = CRGB(val.r * perc, val.g * perc, val.b * perc);
    entries[num_entries++] = newcol;
  }
  
  CRGB getRandom() {
    return entries[random(num_entries)];
  }

  void increaseBrightness() {
    if (intensity < MAX_BRIGHTNESS) intensity += 5;
    updateColors();
  }
  
  void decreaseBrightness() {
    if (intensity > MIN_BRIGHTNESS) intensity -= 5;
    updateColors();
  }
};

//
// utility to slowly fade to a color
//
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
