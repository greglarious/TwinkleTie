//
// pattern with alternating color stripes either falling or going in a circle
//
class CandyCane: public PatternBase {
  const int cane_size = 10;
  const float cane_reduce = 0.5;
  
  int cane_offset=0;
  long next_cane_fade=0;
  int cane_increment = 10;
  bool done_cane_fade = false;
  bool doCircle = false;
  
  CRGB top_color;
  CRGB bottom_color;

public:
  CandyCane(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
    pattern_run_delay = 5;
  }

  void setDoCircle(bool doCircle) {
    this->doCircle = doCircle;
  }
  
  void run() {
    // if it is time to animate the candy cane
    if (timeToRun()) {
      if (doCircle) {
        top_color = CRGB(0, 0, default_palette->getIntensity() * cane_reduce);
        bottom_color = CRGB(default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce);
      } else {
        top_color = CRGB(default_palette->getIntensity() * cane_reduce, 0, 0);
        bottom_color = CRGB(default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce, default_palette->getIntensity() * cane_reduce);
      }
      if (!done_cane_fade) {
        done_cane_fade = true;
        for(byte right_idx=shape->bottom_right; right_idx < shape->top_right; right_idx++) {
          int left_idx;
          if (doCircle)
            left_idx = shape->top_left + right_idx;
          else
            left_idx = shape->bottom_left - right_idx;
          byte colorIndex = (right_idx + cane_offset) % cane_size;
          CRGB newColor;
          if (colorIndex < cane_size / 2)
            newColor = top_color;
          else 
            newColor = bottom_color;
          //if any color is not done fading, keep fading
          if (!FadeUtils::fadeTo(shape->leds, right_idx, newColor, cane_increment)) {
            done_cane_fade = false;
          }
          FadeUtils::fadeTo(shape->leds, left_idx, newColor, cane_increment);
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
      setNextRun();
    } // time to fade
  }
};
