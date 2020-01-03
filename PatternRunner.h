#include <FastLED.h>
#include "FadeUtils.h"
#include "ShapedLED.h"
#include "PatternBase.h"
#include "Twinkler.h"
#include "TwinklerGroup.h" 
#include "Sparkler.h"
#include "ColorPulseWipe.h"
#include "Icicle.h"
#include "CandyCane.h"

#define MODE_OFF 0
#define MODE_SOLID 1
#define MODE_ROLLING 2

#define SPARKLE_PATTERN 0
#define ICICLE_PATTERN 1
#define CANDY_CANE_PATTERN 2
#define CIRCLE_CANE_PATTERN 3
#define UPDOWN_WIPE_PATTERN 4
#define PULSE_PATTERN 5
#define RETRO_TWINKLE_PATTERN 6
#define RAINBOW_TWINKLE_PATTERN 7
#define WHITE_TWINKLE_PATTERN 8
#define MAX_PATTERN_IDX 8

//
// controller to work with a variety of patterns and run/adjust them
//
class PatternRunner {
  const int pattern_display_time = 6000;

  long pattern_end_time = 0;
  int current_pattern_mode = MODE_OFF;
  int current_pattern_idx = SPARKLE_PATTERN;
  PatternBase* cur_pattern = NULL;
  
  ColorPalette default_palette;
  ColorPalette retro;
  ColorPalette classic;
  ColorPalette white;
  
  Sparkler sparkle;
  Icicle icicle;
  CandyCane cane;
  ColorWipe wiper;
  ColorPulser pulser;
  TwinklerGroup twinkler_group;

  ShapedLED* shape;
  
  void turnOff() {
    for (int i=0; i < shape->num_leds; i++) {
      shape->leds[i].r = 0;
      shape->leds[i].g = 0;
      shape->leds[i].b = 0;
    }
    FastLED.show();
  }
  
  void runCurrentPattern() {
    if (cur_pattern != NULL)
      cur_pattern->run();
  }
  
public: 
  PatternRunner(ShapedLED* shape): 
    shape(shape),
    sparkle(shape, &default_palette),
    pulser(shape, &default_palette),
    icicle(shape, &default_palette),
    cane(shape, &default_palette), 
    wiper(shape, &default_palette), 
    twinkler_group(shape, &default_palette) {
      cur_pattern = &sparkle;
  }

  void initPalettes() {
    retro.clearPalette();
    retro.addColor(CRGB::HotPink);
    retro.addColor(CRGB::Turquoise);
    retro.addColor(CRGB::DeepPink);
    retro.addColor(CRGB::Turquoise);
  
    classic.clearPalette();
    classic.addColor(CRGB::Green);
    classic.addColor(CRGB::Blue);
    classic.addColor(CRGB::Red);
    classic.addColor(CRGB::Gold);
  
    white.clearPalette();
    white.addColor(CRGB::AntiqueWhite);    
  }
  
  void runLoop() {
    switch (current_pattern_mode) {
      case MODE_OFF:
        turnOff();
        break;
      case MODE_ROLLING:
        if (millis() > pattern_end_time) {
          nextPattern();
          pattern_end_time = millis() + pattern_display_time;
        }
        runCurrentPattern();
        break;
      case MODE_SOLID:
        runCurrentPattern();
        break;
    }
  }

  void setMode(int new_mode) {
    current_pattern_mode = new_mode;
    if (current_pattern_mode == MODE_OFF)
      turnOff();
  }

  void initPattern() {
    switch(current_pattern_idx) {
      case SPARKLE_PATTERN:
        cur_pattern = &sparkle;
        break;
      case ICICLE_PATTERN:
        cur_pattern = &icicle;
        break;
      case CIRCLE_CANE_PATTERN:
        cane.setDoCircle(true);
        cur_pattern = &cane;
        break;
      case CANDY_CANE_PATTERN:
        cane.setDoCircle(false);
        cur_pattern = &cane;
        break;
      case RETRO_TWINKLE_PATTERN:
        twinkler_group.setup(TwinklerGroup::MAX_TWINKLERS, 0.0, 1.0, 0.03, 50, &retro);
        cur_pattern = &twinkler_group;
        break;
      case RAINBOW_TWINKLE_PATTERN:
        twinkler_group.setup(TwinklerGroup::MAX_TWINKLERS, 0.0, 1.0, 0.03, 50, &classic);
        cur_pattern = &twinkler_group;
        break;
      case WHITE_TWINKLE_PATTERN:
        twinkler_group.setup(TwinklerGroup::MAX_TWINKLERS, 0.0, 1.0, 0.03, 50, &white);
        cur_pattern = &twinkler_group;
        break;
      case UPDOWN_WIPE_PATTERN:
        cur_pattern = &wiper;
        break;
      case PULSE_PATTERN:
        cur_pattern = &pulser;
        break;
    }
  }
  
  void nextPattern() {
    turnOff();
    current_pattern_idx++;
    if (current_pattern_idx > MAX_PATTERN_IDX)
      current_pattern_idx = 0;
    initPattern();  
  }
  
  void prevPattern() {
    turnOff();
    current_pattern_idx--;
    if (current_pattern_idx < 0)
      current_pattern_idx = MAX_PATTERN_IDX;
    initPattern();  
  }

  void increaseBrightness() {
    default_palette.increaseBrightness();
    retro.increaseBrightness();
    classic.increaseBrightness();
    white.increaseBrightness();
    initPalettes();
  }

  void decreaseBrightness() {
    default_palette.decreaseBrightness();
    retro.decreaseBrightness();
    classic.decreaseBrightness();
    white.decreaseBrightness();
    initPalettes();
  }
};
