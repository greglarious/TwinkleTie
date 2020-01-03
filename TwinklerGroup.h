
//
// pattern containing group of twinklers fading in and out of random locations with random colors
//
class TwinklerGroup: public PatternBase {
public:
  static const int MAX_TWINKLERS = 40;

  TwinklerGroup(ShapedLED* shape, ColorPalette* default_palettep): PatternBase(shape, default_palette) {
    pattern_run_delay = 1;
  }

  void setup(const int num_twinklers, const float min_value, const float max_value, const float incrementValue, const int delayValue, ColorPalette *pal ) {
    this->num_twinklers = num_twinklers;
    this->min_value = min_value;
    this->max_value = max_value;
    this->increment = incrementValue;
    this->max_start_delay = delayValue;
    this->palette = pal;
    
    // blank out all positions
    for (int i=0; i < MAX_TWINKLERS; i++) {
      twinkler_positions[i] = -1;
    }
    
    for (int i=0; i < MAX_TWINKLERS; i++) {
      randomize(i);
      twinklers[i].initialize();
    }
  }

  void run() {
    if (timeToRun()) {
      for (int i=0; i < MAX_TWINKLERS; i++) {
        if (twinklers[i].doTwinkle(min_value, max_value, increment, shape->leds)) {
          randomize(i);
        }
      }
      FastLED.show();
      setNextRun();  
    }
  }

private:
  int twinkler_positions[MAX_TWINKLERS];
  int num_twinklers;
  float max_value;
  float min_value;
  float increment;
  byte max_start_delay; 
  ColorPalette *palette;

  Twinkler twinklers[MAX_TWINKLERS];

  boolean checkUsed(int pos) {
    for (int i=0; i < num_twinklers; i++) {
      if (twinkler_positions[i] == pos) {
        return true;
      }
    }
    return false;
  }
    
  void randomize(int index) {
    twinklers[index].setStartupDelay(random(max_start_delay));
    int new_position;
    do {
     new_position = random(shape->num_leds);
    } while (checkUsed(new_position));

    twinklers[index].setPosition(new_position);
    twinkler_positions[index] = new_position;
    twinklers[index].setTargetColor(palette->getRandom());
  }
};
