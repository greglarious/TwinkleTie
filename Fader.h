void eraseTree() {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
  FastLED.show();
}

bool fadeTo(byte index, CRGB target, byte increment) { 
  bool rval= true;
  if (leds[index].r < target.r - increment) {
      leds[index].r+= increment;
      rval = false;
  } else if (leds[index].r > target.r + increment) {
      leds[index].r-= increment;
      rval = false;
  } else {
      leds[index].r = target.r;
  }

  if (leds[index].g < target.g - increment) {
    leds[index].g+= increment;
    rval = false;
  } else if (leds[index].g > target.g + increment) {
    leds[index].g-= increment;
    rval = false;
  } else {
    leds[index].g = target.g;
  }

  if (leds[index].b < target.b - increment) {
    leds[index].b+= increment;
    rval = false;
  } else if (leds[index].b > target.b + increment) {
    leds[index].b-= increment;
    rval = false;
  } else {
    leds[index].b =target.b;
  }
  
  return rval;
  
}

void fadeAllTo(CRGB target, byte increment, int pause) {
  bool done = false;
  while (!done) {
    done = true;
    for(byte idx=0; idx< NUM_LEDS; idx++) {
      if(!fadeTo(idx, target, increment)) {
        done = false;
      }
    }
    FastLED.show();
    delay(pause);
  }
}

// Fill the dots one after the other with a color
void colorWipeUp(CRGB c, byte increment, int speed) {
  for(uint16_t i=bottom_right; i< top_right; i++) {
    bool done = false;
    while (!done) {
      done = true;
      if (!fadeTo(i, c, increment)) {
        done = false;
      }
      fadeTo(bottom_left - i, c, increment);
      FastLED.show();
      delay(speed);
    }
  }
}

void colorWipeDown(CRGB c, byte increment, int pause) {
  for(int i=top_right; i >= bottom_right; i--) {
    bool done = false;
    while (!done) {
      done = true;
      if (!fadeTo(i, c, increment)) {
        done = false;
      }
      fadeTo(top_left + top_right - i, c, increment);
      FastLED.show();
      delay(pause);
    }
  }
}

const int cane_size = 10;
const int cane_delay=5;
const float cane_reduce = 0.5;
int cane_offset=0;
long next_cane_fade=0;
int cane_increment = 10;
bool done_cane_fade = false;


void doCircleCane() {
  // if it is time to animate the candy cane
  if (millis() >= next_cane_fade) {
    CRGB caneBlue = CRGB(0, 0, cIntensity * cane_reduce);
    CRGB caneWhite = CRGB(cIntensity * cane_reduce, cIntensity * cane_reduce, cIntensity * cane_reduce);
    CRGB cane_colors[cane_size] = { caneBlue,caneBlue,caneBlue,caneBlue,caneBlue,  caneWhite,caneWhite,caneWhite, caneWhite, caneWhite  };
    if (!done_cane_fade) {
      done_cane_fade = true;
      for(byte right_idx=bottom_right; right_idx < top_right; right_idx++) {
        int left_idx = top_left + right_idx;
        byte cIndex = (right_idx + cane_offset) % cane_size;
        CRGB newColor = cane_colors[cIndex];
        //if any color is not done fading, keep fading
        if (!fadeTo(right_idx, newColor, cane_increment)) {
          done_cane_fade = false;
        }
        fadeTo(left_idx, newColor, cane_increment);
      }
      FastLED.show();
    } else {
      // move cane down or reset to top
      if (cane_offset < cane_size) {
        cane_offset++;
      } else {
        cane_offset = 0;
      }
      done_cane_fade = false;
    } // done fading
    next_cane_fade = millis() + cane_delay;
  } // time to fade
}

void doCandyCane() {
  // if it is time to animate the candy cane
  if (millis() >= next_cane_fade) {
    CRGB caneRed = CRGB(cIntensity * cane_reduce, 0, 0);
    CRGB caneWhite = CRGB(cIntensity * cane_reduce, cIntensity * cane_reduce, cIntensity * cane_reduce);
    CRGB cane_colors[cane_size] = { caneRed,caneRed,caneRed,caneRed,caneRed,  caneWhite,caneWhite,caneWhite, caneWhite, caneWhite  };
    if (!done_cane_fade) {
      done_cane_fade = true;
      for(byte right_idx=bottom_right; right_idx < top_right; right_idx++) {
        int left_idx = bottom_left - right_idx;
        byte cIndex = (right_idx + cane_offset) % cane_size;
        CRGB newColor = cane_colors[cIndex];
        //if any color is not done fading, keep fading
        if (!fadeTo(right_idx, newColor, cane_increment)) {
          done_cane_fade = false;
        }
        fadeTo(left_idx, newColor, cane_increment);
      }
      FastLED.show();
    } else {
      // move cane down or reset to top
      if (cane_offset < cane_size) {
        cane_offset++;
      } else {
        cane_offset = 0;
      }
      done_cane_fade = false;
    } // done fading
    next_cane_fade = millis() + cane_delay;
  } // time to fade
}

void colorWipes() {
  int pause = 10;
  int inc = 30;
  colorWipeUp( cRed, inc, pause); // Red
  colorWipeDown(cGreen, inc, pause); // Green
}       

void colorPulses() {
  int pause = 10;
  fadeAllTo(cRed, 1, pause);
  delay(300);
  fadeAllTo(cGreen, 1, pause);
  delay(300);
}
