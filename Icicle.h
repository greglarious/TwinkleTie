class Icicle {
  const int icicle_length = 10;
  const int icicle_move_delay = 40;
  const int icicle_color_offset = ColorPalette::MIN_BRIGHTNESS * 0.7;
  
  int icicle_next_move = 0;
  int icicle_pos = tie->top_right;

  TwinkleTie* tie;
  ColorPalette* default_palette;

  void drawIcicle(bool up,int icicle_length, int start, int minIdx, int maxIdx) {
    int icicle_color_decrement = (default_palette->getIntensity() / (icicle_length-1));
    CRGB curColor = CRGB(default_palette->getIntensity() - icicle_color_offset, 
                         default_palette->getIntensity() - icicle_color_offset, 
                         default_palette->getIntensity());
    int curIndex = 0;
    int increment = 1;
    if (!up) increment = -1;
    
    for (curIndex = start; curIndex != start + (icicle_length * increment); curIndex = curIndex + increment) {
      if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
        tie->leds[curIndex] = curColor;
      }
      if (curColor.r >= icicle_color_decrement) curColor.r -= icicle_color_decrement;
      else curColor.r = 0;    
      if (curColor.g >= icicle_color_decrement) curColor.g -= icicle_color_decrement;
      else curColor.g = 0;    
      if (curColor.b >= icicle_color_decrement) curColor.b -= icicle_color_decrement;
      else curColor.b = 0;    
    }
    if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
      tie->leds[curIndex] = default_palette->cBlack;
    }
    FastLED.show();
  }

public:
  Icicle(TwinkleTie* tie, ColorPalette* default_palette): tie(tie), default_palette(default_palette) {
    
  }
  
  void run() {
    if (millis() > icicle_next_move) {
      icicle_next_move = millis() + icicle_move_delay;
      if (icicle_pos >= -icicle_length) {
        icicle_pos--;
        drawIcicle(true,  icicle_length, icicle_pos, tie->bottom_right, tie->top_right);
        drawIcicle(false, icicle_length, tie->top_left + (tie->top_right-icicle_pos), tie->top_left, tie->bottom_left);
      } else {
        icicle_pos = tie->top_right;
      }
    }
  }
};
