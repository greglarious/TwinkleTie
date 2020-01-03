//
// array of LEDs with a visiable shape.
// currently hard coded to a left and right strand as in sides of a necktie. 
// needs work to make this more configurable.
//
class ShapedLED {
public:
  static const int num_leds = 144;
  
  static const uint16_t top_right = num_leds / 2 - 1;
  static const uint16_t bottom_right = 0;
  static const uint16_t top_left = num_leds / 2;
  static const uint16_t bottom_left = num_leds - 1;
  
  CRGB leds[num_leds];

  void setupTie() {
    FastLED.addLeds<WS2811, A1, GRB>(leds, 0, num_leds);
  }
};
