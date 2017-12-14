class ColorPalette {
  CRGB entries[4];
  byte  numEntries;
  
public:
  ColorPalette () {
    numEntries = 0;
  }
  
  void addColor(CRGB val) {
    entries[numEntries++] = val;
  }
  
  CRGB getRandom() {
    return entries[random(numEntries)];
  }
};
