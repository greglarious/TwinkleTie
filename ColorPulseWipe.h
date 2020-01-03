//
// pattern with pulsing between two colors
//
class ColorPulser: public PatternBase {
  bool to_red = true;

public:
  ColorPulser(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
    pattern_run_delay = 10;
  }

  void run() {
    if (timeToRun()) {
      if (to_red) {
        if (FadeUtils::fadeAllTo(shape->leds, shape->num_leds, default_palette->cRed, 1)) {
          to_red = false;
        }
      } else {
        if (FadeUtils::fadeAllTo(shape->leds, shape->num_leds, default_palette->cGreen, 1)) {
          to_red = true;
        }
      }

      FastLED.show();
      setNextRun();
    }
  }
};

//
// pattern with one color wiping up and another wiping down
//
class ColorWipe: public PatternBase {
  int right_position = shape->bottom_right;
  bool fade_completed = false;
  bool wipe_completed = false;
  bool goUp = true;
  int increment = 30;
  CRGB targetColor;
  CRGB upColor;
  CRGB downColor;
  
public:
  ColorWipe(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
    pattern_run_delay = 4;
    setTargetColor(default_palette->cRed);
    reset();
  }

  void setGoingUp(bool goingUp) {
    goUp = goingUp;
    reset();
  }
  
  void setTargetColor(CRGB targetColor) {
    this->targetColor = targetColor;
  }
  
  // Fill the dots one after the other with a color
  void run() {
    wipe_completed = false;
      
    // transition current position to target color
    if (!fade_completed) {
      int left_position = shape->bottom_left - right_position;
      fade_completed = FadeUtils::fadeTo(shape->leds, right_position, targetColor, increment) && FadeUtils::fadeTo(shape->leds, left_position, targetColor, increment);
      FastLED.show();
    }

    // pause before advancing to next positiond
    if (fade_completed && timeToRun()) {
      setNextRun();
      fade_completed = false;
      if (goUp) {
       if (right_position < shape->top_right) {
         right_position++;
         wipe_completed = false;
       }
       else {
         Serial.println("wipe up complete");
         wipe_completed = true;
       }
      } else {
        // going down
        if (right_position > shape->bottom_right) {
          right_position--;
          wipe_completed = false; 
        } else {
         Serial.println("wipe down complete");
          wipe_completed = true;
        }
      }

      if (wipe_completed) {
        if (goUp) {
          setGoingUp(false);
          setTargetColor(default_palette->cGreen);
        } else {
          setGoingUp(true);
          setTargetColor(default_palette->cRed);
        }
      }    
    }

  }

  void reset() {
    wipe_completed = false;
    if (goUp) {
      right_position = shape->bottom_right;
    } else {
      right_position = shape->top_right;
    }
  }

  bool isComplete() {
    return wipe_completed;
  }
};
