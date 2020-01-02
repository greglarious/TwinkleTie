class CandyCane {
  const int cane_size = 10;
  const int cane_delay=5;
  const float cane_reduce = 0.5;
  
  int cane_offset=0;
  long next_cane_fade=0;
  int cane_increment = 10;
  bool done_cane_fade = false;

  CRGB topColor;
  CRGB bottomColor;

  TwinkleTie* tie;
  ColorPalette* default_palette;

public:
  CandyCane(TwinkleTie* tie, ColorPalette* default_palette): tie(tie), default_palette(default_palette) {
  }
  
   void run(bool doCircle) {
    // if it is time to animate the candy cane
    if (millis() >= next_cane_fade) {
      if (doCircle) {
        topColor = CRGB(0, 0, default_palette->getIntensity() * cane_reduce);
        bottomColor = CRGB(default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce);
      } else {
        topColor = CRGB(default_palette->getIntensity() * cane_reduce, 0, 0);
        bottomColor = CRGB(default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce);
      }
      if (!done_cane_fade) {
        done_cane_fade = true;
        for(byte right_idx=tie->bottom_right; right_idx < tie->top_right; right_idx++) {
          int left_idx;
          if (doCircle)
            left_idx = tie->top_left + right_idx;
          else
            left_idx = tie->bottom_left - right_idx;
          byte colorIndex = (right_idx + cane_offset) % cane_size;
          CRGB newColor;
          if (colorIndex < cane_size / 2)
            newColor = topColor;
          else 
            newColor = bottomColor;
          //if any color is not done fading, keep fading
          if (!FadeUtils::fadeTo(tie->leds, right_idx, newColor, cane_increment)) {
            done_cane_fade = false;
          }
          FadeUtils::fadeTo(tie->leds, left_idx, newColor, cane_increment);
        }
        FastLED.show();
      } else {
        // move cane down or reset to top
        if (cane_offset < cane_size) {
          cane_offset++;
        } else {
          cane_offset = 0;
        }
        done_cane_fade = false;
      } // done fading
      next_cane_fade = millis() + cane_delay;
    } // time to fade
  }
};
