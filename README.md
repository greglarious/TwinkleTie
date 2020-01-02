# TwinkleTie
Arduino code for runnng an RGB LED light show on a holiday necktie controlled via bluetooth.
TL/DR: Rudolph with your tie so bright, turn that thing down before you harm someone's retina.

## Demonstration
[![Demonstration Video](https://i.ytimg.com/vi/MoQlWXUC1UQ/0.jpg)](https://youtu.be/MoQlWXUC1UQ)

## Schematic
<img src="https://github.com/greglarious/TwinkleTie/blob/master/TwinkleTieSchematic.png?raw=true" width="500" height="500" />

## Parts List:
- One WS2812B LED strip. 1m, 144LEDS [WS2812 strips](https://www.google.com/search?q=BTF-LIGHTING+WS2812B+144+LEDs) 
- [Adafruit Feather M0 Bluefruit LE](https://www.adafruit.com/product/2995)
- [2500mah 3.7v lion battery](https://www.adafruit.com/product/328)
- Ridiculous necktie

## Notes
- Controllers with 5V logic levels are a sure bet when driving WS2811 and WS2812 LEDs but
- In recent years I have had very good results with 3V controllers. In this project we are using a 3V controller and also driving the strip itself with only 3.7V. Having the battery voltage just 0.7v away from the driving voltage makes it more reliable and there is no noticeable sacrifice in brightness for driving it with 1.3V less than usual 
- When soldering to RGB LED strips, the joint can be fragile so it is very helpful to reinforce the solder locations with epoxy to provide durability
