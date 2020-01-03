//
// base for all runnable patterns
//
class PatternBase {
protected:
  int pattern_run_delay;
  long next_pattern_run;

  ShapedLED* shape;
  ColorPalette* default_palette;

  bool timeToRun() {
    return millis() >= next_pattern_run;
  }

  void setNextRun() {
    next_pattern_run = millis() + pattern_run_delay;
  }
  
public:
  PatternBase(ShapedLED* shape, ColorPalette* default_palette): shape(shape), default_palette(default_palette) {
    next_pattern_run=0;
  }

  virtual void run() {
    
  }
};
