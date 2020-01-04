# TwinkleTie
Arduino code for runnng an RGB LED light show on a holiday necktie remote controlled via bluetooth.
TL/DR: Rudolph with your tie so bright, turn that thing down before you harm someone's retina.

## Demonstration
-Short demo of overall functionality and basic parts:

[![Demonstration Video](https://img.youtube.com/vi/xrCQoonOee4/default.jpg)](https://www.youtube.com/watch?v=xrCQoonOee4)

-Overview of the LED Patterns:

[![Pattern overview Video](https://img.youtube.com/vi/lUyAfUY4ZbM/default.jpg)](https://www.youtube.com/watch?v=lUyAfUY4ZbM)

-Stranger Lights Pattern:

[![Stranger Lights pattern Video](https://img.youtube.com/vi/v92BPB_iMAA/default.jpg)](https://www.youtube.com/watch?v=v92BPB_iMAA)

## Schematic
This schematic is out of date from an older version that used 2 strips. The latest iteration uses just 1.
<img src="https://github.com/greglarious/TwinkleTie/blob/master/TwinkleTieSchematic.png?raw=true" width="500" height="500" />

## Parts List:
- LED strip. 1m, 144LEDS. See notes below on differences and choosing. The video demo shows a generic brand strip without waterproofing.
  - [first choice: generic brand WS2812 144/m strip - with adhesive](https://www.google.com/search?q=BTF-LIGHTING+WS2812B+144+LEDs) 
  - [alternate: Adafruit NeoPixel 144/m strip - no adhesive](https://www.adafruit.com/product/1506)
  - [alternate: Adafruit NeoPixel 144/m mini skinny strip - no adhesive](https://www.adafruit.com/product/2970)
- Microcontroller [Adafruit Feather M0 Bluefruit LE](https://www.adafruit.com/product/2995)
  - Arduino compatible
  - Fast, plenty of memory, lots of pins
  - Builtin bluetooth
  - Builtin connector for battery
  - Recharges battery (slowly) when USB is connected
- Battery [2500mah 3.7v lion battery](https://www.adafruit.com/product/328)
- Ridiculous necktie, bowtie, suspenders, hat ...
- (optional) [Faster USB lipo charger](https://www.adafruit.com/product/1904)

## Notes
- LED strip waterproof rating and sticky tape backing:
  - IP30 rating means not waterproof. these usually come with a peel and stick backing
  - IP65 rating means waterproof to low pressure spray. These strips usually have a slightly rigid, curved, crystal clear silicone coating on one side and a peel and stick backing
  - IP67 rating means highly waterproof. These strips are usually inside a flexible rectangular silicone case that is not perfectly clear. This form of LED strip does not offer a peel and stick backing. Mounting is usually done with plastic brackets. I have not yet tried to build a tie with an IP67 strip and not sure how mounting would work. Maybe sew it to the tie?
- Microcontroller logic voltage vs LED logic voltage vs LED illumination voltage:
  - Logic voltage on microcontrollers is available in 5V and 3V formats
  - Logic voltage on addressable LEDs (WS2811 and WS2812) is 5v
  - Illumination voltage on addressable LEDS is 5V for this project but 12V is also available
  - A controller board with 5V logic levels is a sure bet when driving these LEDs but in recent years I have had very good results with 3V controllers directly connected to short LED strips 
  - In this project I am using a 3V controller and driving the illumination with only 3.7V with great results
  - Having the illumination voltage just 0.7v above the driving voltage of 3V actually makes it more reliable and there is no noticeable sacrifice in brightness from using a driving that is 1.3V less than usual  
- Construction tips:
  - The overall durability of a necktie with an LED strip stuck onto it is fairly low. I leave the knot permanently tied and loosen it just enough to pull over my head
  - Use something like a zip tie to anchor the LED control wires firmly to the controller board so the solder joints are not stressed and broken from normal use of the tie
  - Consider IP65 as more likely to survive stains!
  - If the weight of the LED strips causes the tie to lose its shape, you can insert a semi-rigid material such as leather inside of the tie to help retain a nice shape
  - In general, don't hesitate to remove threads holding the back of the tie together and re-sew after parts are in place. None of that will be visible from the front.
  - If you have to solder directly onto the LED strip, the joint can be fragile so it is very helpful to reinforce the solder locations with epoxy to provide durability
  - Best not to solder header pins onto the controller to keep the end result as flat as possible
