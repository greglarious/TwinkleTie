#define icicle_size 10
#define icicle_speed 40
#define icicle_dec (iIntensity / (icicle_length-1))
const CRGB icicle_color = CRGB(iIntensity-45, iIntensity-45, iIntensity);

void drawIcicle(bool up,int icicle_length, int start, int minIdx, int maxIdx) {
  CRGB curColor = icicle_color;
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

void fallingIcicle() {
  for (int index=top_right; index >= -icicle_size; index--) { 
    drawIcicle(true,  icicle_size, index, bottom_right, top_right);
    drawIcicle(false, icicle_size, top_left + (top_right-index), top_left, bottom_left);
    delay(icicle_speed);
  }
}
