float MIN_VALUE;
float MAX_VALUE;
int MAX_DELAY_BETWEEN_TWINKLES;
float TWINKLE_INCREMENT;
int DELAY_BETWEEN_INCREMENTS;
int NUM_TWINKLE;

Twinkler twinklers[MAX_TWINKLERS];
ColorPalette *cur_palette;

ColorPalette retro;
ColorPalette classic;
ColorPalette white;
boolean isSetup = false;

void setupTwinkler(int num_leds) {
  if (!isSetup) {
    retro.addColor(CRGB::HotPink);
    retro.addColor(CRGB::Turquoise);
    retro.addColor(CRGB::DeepPink);
    retro.addColor(CRGB::Turquoise);
  
    classic.addColor(CRGB::Green);
    classic.addColor(CRGB::Blue);
    classic.addColor(CRGB::Red);
    classic.addColor(CRGB::Gold);
  
    white.addColor(CRGB::AntiqueWhite);
    isSetup = true;
  }
  
  Twinkler::setup(NUM_TWINKLE, num_leds, MIN_VALUE, MAX_VALUE, TWINKLE_INCREMENT, MAX_DELAY_BETWEEN_TWINKLES, cur_palette);

  for (int i=0; i < NUM_TWINKLE; i++) {
    twinklers[i].initialize(i);
  }
}

void setClassicWhiteTwinkle(int num_leds) {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = MAX_TWINKLERS;
 cur_palette = &white;
 setupTwinkler(num_leds);
}

void setRetroTwinkle(int num_leds) {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = MAX_TWINKLERS;
 cur_palette = &retro;
 setupTwinkler(num_leds);
}

void setupRainbowTwinkle(int num_leds) {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = MAX_TWINKLERS;
 cur_palette = &classic;
 setupTwinkler(num_leds);
}

long next_twinkle_time = 0;

void loopTwinkler(CRGB* leds)
{
  if (millis() > next_twinkle_time) {
    for (int i=0; i < NUM_TWINKLE; i++) {
      twinklers[i].doTwinkle();
      twinklers[i].setInto(leds);
    }
    FastLED.show();
    next_twinkle_time = millis() + DELAY_BETWEEN_INCREMENTS;  
  }
}
