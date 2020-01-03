//
// patern with falling icicle
//
class Icicle: public PatternBase {
  const int icicle_length = 10;
  const int icicle_color_offset = ColorPalette::MIN_BRIGHTNESS * 0.7;
  
  int icicle_pos = shape->top_right;

  void drawIcicle(bool up,int icicle_length, int start, int minIdx, int maxIdx) {
    int icicle_color_decrement = (default_palette->getIntensity() / (icicle_length-1));
    CRGB cur_color = CRGB(default_palette->getIntensity() - icicle_color_offset, 
                         default_palette->getIntensity() - icicle_color_offset, 
                         default_palette->getIntensity());
    int cur_index = 0;
    int increment = 1;
    if (!up) increment = -1;
    
    for (cur_index = start; cur_index != start + (icicle_length * increment); cur_index = cur_index + increment) {
      if ((cur_index >= minIdx) && (cur_index <= maxIdx)) {
        shape->leds[cur_index] = cur_color;
      }
      if (cur_color.r >= icicle_color_decrement) cur_color.r -= icicle_color_decrement;
      else cur_color.r = 0;    
      if (cur_color.g >= icicle_color_decrement) cur_color.g -= icicle_color_decrement;
      else cur_color.g = 0;    
      if (cur_color.b >= icicle_color_decrement) cur_color.b -= icicle_color_decrement;
      else cur_color.b = 0;    
    }
    if ((cur_index >= minIdx) && (cur_index <= maxIdx)) {
      shape->leds[cur_index] = default_palette->cBlack;
    }
    FastLED.show();
  }

public:
  Icicle(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
  }
  
  void run() {
    if (timeToRun()) {
      setNextRun();
      if (icicle_pos >= -icicle_length) {
        icicle_pos--;
        drawIcicle(true,  icicle_length, icicle_pos, shape->bottom_right, shape->top_right);
        drawIcicle(false, icicle_length, shape->top_left + (shape->top_right-icicle_pos), shape->top_left, shape->bottom_left);
      } else {
        icicle_pos = shape->top_right;
      }
    }
  }
};
