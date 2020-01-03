//
// pattern with sparkles appearing in random locations
//
class Sparkler: public PatternBase {
  const static int num_sparkles = 30;
  int sparkle_positions[num_sparkles];
public:
  Sparkler(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
    pattern_run_delay = 40;
  }
  
  void run() {
    if (timeToRun()) {
      setNextRun();
      for (int i=0; i< num_sparkles; i++) {
        shape->leds[sparkle_positions[i]] = default_palette->cBlack;
        sparkle_positions[i] = random(shape->num_leds);
        shape->leds[sparkle_positions[i]] = default_palette->cWarmWhite;
      }
      FastLED.show(); 
    }
  }
};
