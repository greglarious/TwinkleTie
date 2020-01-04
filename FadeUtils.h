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

  static CRGB adjustColor(CRGB color, float intensity) {
    CRGB rval = CRGB(
        min(255,max(0,(float)color.r * intensity)), 
        min(255,max(0,(float)color.g * intensity)), 
        min(255,max(0,(float)color.b * intensity)));
    return rval;
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

class Flicker {
  bool blink_phase = false;
  bool returning_to_start = false;
  float cur_intensity = -1;

  void updateIntensity( float begin_intensity, float end_intensity, float intensity_increment) {
    if (end_intensity < begin_intensity) {
      cur_intensity = cur_intensity - intensity_increment;
    } else {
      cur_intensity = cur_intensity + intensity_increment;      
    } 
    
    if (cur_intensity > max(begin_intensity, end_intensity)) {
      cur_intensity = max(begin_intensity, end_intensity);
    }
    if (cur_intensity < min(begin_intensity, end_intensity)) {
      cur_intensity = min(begin_intensity, end_intensity);
    }    
  }

public:
  float getIntensity() {
    return cur_intensity;
  }
  
  //
  // fade one LED up or down between two brightness levels while alternating with black to produce a flicker effect
  //
  bool flicker(int start_position, int end_position, CRGB leds[], float start_intensity, float target_intensity, float flick_down_intensity, bool do_return_to_start,
    CRGB base_colors[], float intensity_increment, int num_leds) {    
    float begin_intensity = start_intensity;
    float end_intensity = target_intensity;
    
    if (cur_intensity < 0) {
      // begin flicker
      cur_intensity = begin_intensity;
      returning_to_start = false;
    }

    // if returning, swap start and target
    if (returning_to_start) {
      begin_intensity = target_intensity;
      end_intensity = start_intensity;
    }

    if (blink_phase) {
      for (int index = start_position; index <= end_position; index++) {
        leds[index] = ColorPalette::adjustColor(base_colors[index], flick_down_intensity);        
      }        
    } else {
      for (int index = start_position; index <= end_position; index++) {
        leds[index] = ColorPalette::adjustColor(base_colors[index], cur_intensity);        
      }
      updateIntensity(begin_intensity, end_intensity, intensity_increment);

      if (cur_intensity == end_intensity) {
        if (do_return_to_start && !returning_to_start) {
          returning_to_start = true;
        } else {
          // done flickering
          cur_intensity = -1;
        }
      }

    }

    // alternate to and from blinking phase
    blink_phase = !blink_phase;

    return cur_intensity == -1;
  } 
};
