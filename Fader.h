const CRGB circle_colors[cane_size] = { cBlue,cBlue,cBlue,cBlue,cBlue,  cWhite,cWhite,cWhite, cWhite, cWhite  };
const CRGB cane_colors[cane_size] = { cRed,cRed,cRed,cRed,cRed,  cWhite,cWhite,cWhite, cWhite, cWhite  };

void eraseTree() {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
  FastLED.show();
}

bool fadeTo(byte index, CRGB target, byte increment) {
//  Serial.print("fade to index:");
// Serial.println(index);
//  leds[index] = target;
//  return true;
  
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

void circleCane() {
  int increment = 15;
  for (int offset=0; offset < cane_size; offset++) {
    bool done = false;
    while (!done) {
      done = true;
      for(byte right_idx=bottom_right; right_idx < top_right; right_idx++) {
        int left_idx = top_left + right_idx;
        byte cIndex = (right_idx + offset) % cane_size;
        CRGB newColor = circle_colors[cIndex];
        if (!fadeTo(right_idx, newColor, increment)) {
          done = false;
        }
        fadeTo(left_idx, newColor, increment);
      }
      FastLED.show();
      delay(1);
    }
  }
}

void candyCane() {
  int increment = 10;
  for (int offset=0; offset < cane_size; offset++) {
    bool done = false;
    while (!done) {
      done = true;
      for(byte right_idx=bottom_right; right_idx < top_right; right_idx++) {
        int left_idx = bottom_left - right_idx;
        byte cIndex = (right_idx + offset) % cane_size;
        CRGB newColor = cane_colors[cIndex];
        if (!fadeTo(right_idx, newColor, increment)) {
          done = false;
        }
        fadeTo(left_idx, newColor, increment);
      }
      FastLED.show();
      delay(5);
    }
  }
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
