class Sparkler {
  const static int num_sparkles = 30;
  const static int sparkle_millis = 40;

  int sparkle_positions[num_sparkles];
  long next_sparkle_time = 0;

  CRGB* leds;
  int num_leds;
  ColorPalette* default_palette;

public:

  Sparkler(CRGB* leds, int num_leds, ColorPalette* default_palette): leds(leds), num_leds(num_leds), default_palette(default_palette) {
    
  }
  
  void run() {
    if (millis() > next_sparkle_time) {
      next_sparkle_time = millis() + sparkle_millis;
      for (int i=0; i< num_sparkles; i++) {
        leds[sparkle_positions[i]] = default_palette->cBlack;
        sparkle_positions[i] = random(num_leds);
        leds[sparkle_positions[i]] = default_palette->cWarmWhite;
      }
      FastLED.show(); 
    }
  }
};
