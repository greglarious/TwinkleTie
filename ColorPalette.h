class ColorPalette {
  CRGB entries[4];
  byte  numEntries;
  int cIntensity;
public:
  ColorPalette (int intensity) {
    numEntries = 0;
    cIntensity = intensity;
  }
  
  void addColor(CRGB val) {
    float perc = (float)(cIntensity / 255.0) * 2;
    CRGB newcol = CRGB(val.r * perc, val.g * perc, val.b * perc);
    Serial.print("perc:");
    Serial.println(perc);
    entries[numEntries++] = newcol;
  }
  
  CRGB getRandom() {
    return entries[random(numEntries)];
  }
};
