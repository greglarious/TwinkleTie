void eraseTree() {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
  FastLED.show();
}

bool fadeTo(byte index, CRGB target, byte increment) {
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

void fadeAllTo(CRGB target, byte increment) {
  bool done = false;
  while (!done) {
    done = true;
    for(byte idx=0; idx< 30; idx++) {
      if(!fadeTo(idx, target, increment)) {
        done = false;
      }
    }
    FastLED.show();
  }
}

// Fill the dots one after the other with a color
void colorWipeUp(CRGB c, byte increment) {
  for(uint16_t i=0; i< 15; i++) {
    bool done = false;
    while (!done) {
      done = true;
      if (!fadeTo(i, c, increment)) {
        done = false;
      }
      fadeTo(i+15, c, increment);
      FastLED.show();
    }
  }
}

void colorWipeDown(CRGB c, byte increment) {
  for(int i=15-1; i >= 0; i--) {
    bool done = false;
    while (!done) {
      done = true;
      if (!fadeTo(i, c, increment)) {
        done = false;
      }
      fadeTo(i+15, c, increment);
      FastLED.show();
    }
  }
}

void candyCane() {
  int increment = 1;
  for (int offset=0; offset < 6; offset++) {
    bool done = false;
    while (!done) {
      done = true;
      for(byte idx=0; idx< 15; idx++) {
        byte cIndex = (idx + offset) % 6;
        CRGB newColor = colors[cIndex];
        if(!fadeTo(idx, newColor, increment)) {
          done = false;
        }
        fadeTo(idx +15, newColor, increment);
      }
      FastLED.show();
    }
  }
}

void colorWipes() {
  colorWipeUp( cRed, 1); // Red
  colorWipeDown(cGreen, 1); // Green
}       

void colorPulses() {
  fadeAllTo(cRed, 1);
  delay(500);
  fadeAllTo(cGreen, 1);
  delay(500);
}

void drawIcicle(int index, int minIdx, int maxIdx) {
  CRGB curColor =  CRGB(210, 210, 255);
  int curIndex = 0;
  for (curIndex = index; curIndex < (index + 6); curIndex++) {
    if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
      leds[curIndex] = curColor;
    }
    int dec = 50;
    if (curColor.r >= dec) curColor.r -= dec;
    else curColor.r = 0;    
    if (curColor.g >= dec) curColor.g -= dec;
    else curColor.g = 0;    
    if (curColor.b >= dec) curColor.b -= dec;
    else curColor.b = 0;    
  }
  if ((curIndex >= minIdx) && (curIndex <= maxIdx)) {
    leds[curIndex] = cBlack;
  }
  FastLED.show();
}

void fallingIcicle() {
  for (int index=14; index >= -4; index--) { 
    drawIcicle(index, 0, 14);
    drawIcicle(index+15, 15, 29);
    delay(80);
  }
}
