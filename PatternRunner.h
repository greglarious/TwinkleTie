// patterns not related to tie shape
#include "Twinkler.h" 
#include "TwinklePatterns.h"
#include "Sparkler.h"
#include "ColorPulser.h"

// patterns that depend on the tie shape
#include "Icicle.h"
#include "CandyCane.h"
#include "ColorWipe.h"

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
    
class PatternRunner {
  const int patternLength = 6000;

  long pattern_end_time = 0;
  int current_pattern_mode = MODE_OFF;
  int current_pattern_idx = SPARKLE_PATTERN;

  ColorPalette* palette;
  Sparkler sparkle;
  Icicle icicle;
  CandyCane cane;
  ColorWipe wiper1;
  ColorWipe wiper2;
  ColorPulser pulser;

  TwinkleTie* tie;
  
  void turnOff() {
    for (int i=0; i < tie->NUM_LEDS; i++) {
      tie->leds[i].r = 0;
      tie->leds[i].g = 0;
      tie->leds[i].b = 0;
    }
    FastLED.show();
  }
  
  void upDownWipe() {
    int pause = 2;
    int inc = 30;
    if (!wiper1.isComplete()) {
      wiper1.run(palette->cRed, inc, pause);
    } else if (!wiper2.isComplete()) {
        wiper2.run(palette->cGreen, inc, pause);
    } else {
      wiper1.reset();
      wiper2.reset();
    }
  }
  
  void runCurrentPattern() {
    switch (current_pattern_idx) {
      case SPARKLE_PATTERN:
        sparkle.run();
        break;
      case ICICLE_PATTERN:
        icicle.run();
        break;
      case CANDY_CANE_PATTERN:
        cane.run(false);
        break;
      case CIRCLE_CANE_PATTERN:
        cane.run(true);
        break; 
      case UPDOWN_WIPE_PATTERN:
        upDownWipe();
        break;
      case PULSE_PATTERN:
        pulser.run();
        break;
      case RETRO_TWINKLE_PATTERN:
      case RAINBOW_TWINKLE_PATTERN:
      case WHITE_TWINKLE_PATTERN:
        loopTwinkler(tie->leds);
        break;
    }
  }
public: 
  PatternRunner(TwinkleTie* tie, ColorPalette* palette): 
    tie(tie),
    palette(palette), 
    sparkle(tie->leds, tie->NUM_LEDS, palette),
    pulser(tie->leds, tie->NUM_LEDS, palette),
    icicle(tie, palette),
    cane(tie, palette), 
    wiper1(tie, palette, true), 
    wiper2(tie, palette, false) {
  }

  void runLoop() {
    switch (current_pattern_mode) {
      case MODE_OFF:
        turnOff();
        break;
      case MODE_ROLLING:
        if (millis() > pattern_end_time) {
          nextPattern();
          pattern_end_time = millis() + patternLength;
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

  void initTwinklers() {
    switch(current_pattern_idx) {
      case RETRO_TWINKLE_PATTERN:
        setRetroTwinkle(tie->NUM_LEDS);
        break;
      case RAINBOW_TWINKLE_PATTERN:
        setupRainbowTwinkle(tie->NUM_LEDS);
        break;
      case WHITE_TWINKLE_PATTERN:
        setClassicWhiteTwinkle(tie->NUM_LEDS);
        break;
    }
  }
  
  void nextPattern() {
    turnOff();
    current_pattern_idx++;
    if (current_pattern_idx > MAX_PATTERN_IDX)
      current_pattern_idx = 0;
    initTwinklers();  
  }
  
  void prevPattern() {
    turnOff();
    current_pattern_idx--;
    if (current_pattern_idx < 0)
      current_pattern_idx = MAX_PATTERN_IDX;
    initTwinklers();  
  }
};
