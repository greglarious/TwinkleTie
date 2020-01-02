class ColorPulser {
  bool toRed = true;
  int fade_delay = 10;
  long time_to_fade = 0;

  CRGB* leds;
  int num_leds;
  ColorPalette* default_palette;
public:
  ColorPulser(CRGB* leds, int num_leds, ColorPalette* default_palette): leds(leds), num_leds(num_leds), default_palette(default_palette) {
  }

  void run() {
    if (millis() >= time_to_fade) {
      if (toRed) {
        if (FadeUtils::fadeAllTo(leds, num_leds, default_palette->cRed, 1)) {
          toRed = false;
        }
      } else {
        if (FadeUtils::fadeAllTo(leds, num_leds, default_palette->cGreen, 1)) {
          toRed = true;
        }
      }

      FastLED.show();
      time_to_fade = millis() + fade_delay;
    }
  }
};
