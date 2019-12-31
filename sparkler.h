const int numSparkle = 30;
int curIndex[numSparkle];
int sparkleLength = 40;
long nextSparkle = 0;

void doSparkler() {
  if (millis() > nextSparkle) {
    nextSparkle = millis() + sparkleLength;
    for (int i=0; i< numSparkle; i++) {
      leds[curIndex[i]] = cBlack;
      curIndex[i] = random(NUM_LEDS);
      leds[curIndex[i]] = cWarmWhite;
    }
    FastLED.show(); 
  }
}
