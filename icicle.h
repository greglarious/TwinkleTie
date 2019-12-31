#define icicle_size 10
#define icicle_speed 40
#define icicle_dec (cIntensity / (icicle_length-1))
#define icicle_color_offset 45

void drawIcicle(bool up,int icicle_length, int start, int minIdx, int maxIdx) {
  CRGB curColor = CRGB(cIntensity-icicle_color_offset, cIntensity-icicle_color_offset, cIntensity);
  int curIndex = 0;
  int increment = 1;
  if (!up) increment = -1;
  
  for (curIndex = start; curIndex != start + (icicle_length * increment); curIndex = curIndex + increment) {
    if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
      leds[curIndex] = curColor;
    }
    if (curColor.r >= icicle_dec) curColor.r -= icicle_dec;
    else curColor.r = 0;    
    if (curColor.g >= icicle_dec) curColor.g -= icicle_dec;
    else curColor.g = 0;    
    if (curColor.b >= icicle_dec) curColor.b -= icicle_dec;
    else curColor.b = 0;    
  }
  if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
    leds[curIndex] = cBlack;
  }
  FastLED.show();
}

int icicle_move = 0;
int icicle_pos = top_right;

void doIcicle() {
  if (millis() > icicle_move) {
    icicle_move += icicle_speed;
    if (icicle_pos >= -icicle_size) {
      icicle_pos--;
      drawIcicle(true,  icicle_size, icicle_pos, bottom_right, top_right);
      drawIcicle(false, icicle_size, top_left + (top_right-icicle_pos), top_left, bottom_left);
    } else {
      icicle_pos = top_right;
    }
  }
}
