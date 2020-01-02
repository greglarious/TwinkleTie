class ColorWipe {
  int right_position = tie->bottom_right;
  long next_move_time = 0;
  bool fade_completed = false;
  bool wipe_completed = false;
  bool goUp = false;


  TwinkleTie* tie;
  ColorPalette* default_palette;
  
public:
  ColorWipe(TwinkleTie* tie, ColorPalette* default_palette, bool goingUp): tie(tie), default_palette(default_palette), goUp(goingUp) {
    reset();
  }
  
  // Fill the dots one after the other with a color
  void run(CRGB targetColor, byte increment, int wipe_delay) {
    wipe_completed = false;
      
    // transition current position to target color
    if (!fade_completed) {
      int left_position = tie->bottom_left - right_position;
      fade_completed = FadeUtils::fadeTo(tie->leds, right_position, targetColor, increment) && FadeUtils::fadeTo(tie->leds, left_position, targetColor, increment);
      FastLED.show();
      
      if (fade_completed) {
        next_move_time = millis() + wipe_delay;
      }
    }

    // pause before advancing to next positiond
    if (fade_completed && millis() > next_move_time) {
      fade_completed = false;
      if (goUp) {
       if (right_position < tie->top_right) {
         right_position++;
         wipe_completed = false;
       }
       else {
         // reset for next pass
         right_position = tie->bottom_right;
         wipe_completed = true;
       }
      } else {
        // going down
        if (right_position >= tie->bottom_right) {
          right_position--;
          wipe_completed = false; 
        } else {
          // reset for next pass
          right_position = tie->top_right;
          wipe_completed = true;
        }
      }
    }
  }

  void reset() {
    wipe_completed = false;
    if (goUp) {
      right_position = tie->bottom_right;
    } else {
      right_position = tie->top_right;
    }
  }

  bool isComplete() {
    return wipe_completed;
  }
};
