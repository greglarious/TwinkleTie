float MIN_VALUE;
float MAX_VALUE;
int MAX_DELAY_BETWEEN_TWINKLES;
float TWINKLE_INCREMENT;
int DELAY_BETWEEN_INCREMENTS;
int NUM_TWINKLE;

Twinkler twinklers[10];
ColorPalette *palette;

ColorPalette retro;
ColorPalette classic;
ColorPalette white;

boolean isSetup = false;

void setupTwinkler() {
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
  
  Twinkler::setup(NUM_TWINKLE, NUM_LEDS, MIN_VALUE, MAX_VALUE, TWINKLE_INCREMENT, MAX_DELAY_BETWEEN_TWINKLES, palette);

  for (int i=0; i < NUM_TWINKLE; i++) {
    twinklers[i].initialize(i);
  }
}

void setClassicWhiteTwinkle() {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = 10;
 palette = &white;
 setupTwinkler();
}

void setRetroTwinkle() {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = 10;
 palette = &retro;
 setupTwinkler();
}

void setupRainbowTwinkle() {
 MIN_VALUE = 0.0;
 MAX_VALUE = 1.0;
 MAX_DELAY_BETWEEN_TWINKLES = 100;
 TWINKLE_INCREMENT = 0.01;
 DELAY_BETWEEN_INCREMENTS = 1;
 NUM_TWINKLE = 10;
 palette = &classic;
 setupTwinkler();
}



void loopTwinkler()
{
  //Serial.println("loop twinkler:");

  for (int i=0; i < NUM_TWINKLE; i++) {
    twinklers[i].doTwinkle();
    twinklers[i].setInto(leds);
  }
  FastLED.show();  
  delay(DELAY_BETWEEN_INCREMENTS);  
}

