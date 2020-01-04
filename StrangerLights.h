//
// strange creepy pattern with a side of demigorgon
//
class StrangerLights: public PatternBase {
  enum LightMode { Normal, Stutter, ShortCircuit, BrownOut, Demogorgon };

  const int stutter_odds = 12;
  const int burnout_odds = 8;
  const int short_circuit_odds = 110;
  const int brownout_odds = 90;  
  const float brightness_reduction = 0.6;

  CRGB color_bases[ShapedLED::num_leds];
  Flicker primary;
  Flicker effect;
  float stutter_amount = 0.2;
  int current_position = 0;
  LightMode current_mode = Normal;
  int demo_phase = 0;
  
  void randomizeColor(int idx) {
    // sometimes skip an led leaving it dark to simulate a burned out bulb
    if (random(burnout_odds) == 0) {
        color_bases[idx].r = 0;
        color_bases[idx].b = 0; 
        color_bases[idx].b = 0;
    } else { 
      color_bases[idx].r = random(default_palette->getIntensity() * brightness_reduction);
      color_bases[idx].g = random(default_palette->getIntensity() * brightness_reduction); 
      color_bases[idx].b = random(default_palette->getIntensity() * brightness_reduction); 
    }
  }

  bool nextPosition() {
    bool more_positions = true;
    // current led at max intensity, go to next led
    if (current_position < (shape->num_leds - 1)) {
      current_position++;
      randomizeColor(current_position);
    } else {
      more_positions = false;
    }
    return more_positions;
  }

  void badThingsHappen() {
    if (primary.getIntensity() > (stutter_amount + 0.2) && random(stutter_odds) == 1) {
      current_mode = Stutter;
    } else if (random(short_circuit_odds) == 1) {
      current_mode = ShortCircuit;
    } else if (random(brownout_odds) == 1) {
      current_mode = BrownOut;
    }
  }

  void doDemogorgon() {
    bool all_fade_complete = true;

    switch(demo_phase) {
    case 2:
    case 0:
      for (int index = 0; index < shape->num_leds; index++) {
        if (!FadeUtils::fadeTo(shape->leds, index, default_palette->cWhite, 1)) {
          all_fade_complete = false;
        }
      }
      break;
    case 3:
    case 1:
      for (int index = 0; index < shape->num_leds; index++) {
        if (!FadeUtils::fadeTo(shape->leds, index, color_bases[index], 1)) {
          all_fade_complete = false;
        }
      }
      break;
    case 4:
      for (int index = 0; index < shape->num_leds; index++) {
        shape->leds[index] = default_palette->cBlack;
        color_bases[index] = default_palette->cBlack;
      }
      current_position = 0;
      current_mode = Normal;
      break;
    }
    
    if (all_fade_complete) {
        demo_phase++;
    }
  }

public:
  StrangerLights(ShapedLED* shape, ColorPalette* default_palette): PatternBase(shape, default_palette) {
    pattern_run_delay = 11;
  }

  void run() {
    if (timeToRun()) {
      setNextRun();
      
      int num_flickers = 3 + random(6);
      float intensity_increment = 0.9 / (float)num_flickers;

      switch (current_mode) {
        case Normal:
          if (primary.flicker(current_position, current_position, shape->leds, 0.1, 1.0, 0.01, false, color_bases, intensity_increment, shape->num_leds)) {
            if (!nextPosition()) {
              current_mode = Demogorgon;
              demo_phase  = 0;
            }
          } else {
            badThingsHappen();
          }
          break;
        case Stutter:
          if (effect.flicker(current_position, current_position, shape->leds, primary.getIntensity(), primary.getIntensity() - stutter_amount, 0.01, true, color_bases, intensity_increment, shape->num_leds))
          {
            current_mode = Normal;                      
          }
          break;
        case ShortCircuit:
          // flicker all leds quickly down to almost off and back up
          if (effect.flicker(0, current_position, shape->leds, 1.0, 0.2, 0.0, true, color_bases, 0.3, shape->num_leds)) {
            current_mode = Normal;
          }
          break;
        case BrownOut:
          // flicker all leds slowly down and up just a bit
          if (effect.flicker(0, current_position, shape->leds, 1.0, 0.6, 0.3, true, color_bases, 0.02, shape->num_leds)) {
            current_mode = Normal;
          }
          break;
        case Demogorgon:
          doDemogorgon();
          break;
      }
      FastLED.show(); 
    }
  }
};
