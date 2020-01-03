//
// utility to fade a color in and out
//
class Twinkler {
  float value;
  boolean up;
  byte startup_delay;
  CRGB target_color;
  int led_position;

public:
  Twinkler() {
    initialize();
  }
  
  void initialize() {
    value = 0;
    up = true;
  }

  void setStartupDelay(byte new_delay) {
    startup_delay = new_delay;
  }

  void setTargetColor(CRGB new_color) {
    target_color = new_color;
  }

  void setPosition(int new_position) {
    led_position = new_position;
  }
  bool doTwinkle(float minVal, float maxVal, float increment, CRGB leds[]) {
    bool completed = false;
    if (startup_delay > 0) {
      startup_delay--;
    } else {
      if (up) {
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
          completed = true;
        }
      }
      setInto(leds);
    }
    return completed;
  }
  
  void setInto(CRGB leds[]) {
    leds[led_position] = getValue();
  }

private:
  CRGB getValue() {
    CRGB rval;
    
    rval.r = (float)target_color.r * value;
    rval.g = (float)target_color.g * value;
    rval.b = (float)target_color.b * value;
    return rval;
  }
};
