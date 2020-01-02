# TwinkleTie
Arduino code for runnng an RGB LED light show on a holiday necktie controlled via bluetooth.
TL/DR: Rudolph with your tie so bright, turn that thing down before you harm someone's retina.

## Demonstration
[![Demonstration Video](https://i.ytimg.com/vi/MoQlWXUC1UQ/0.jpg)](https://youtu.be/MoQlWXUC1UQ)

## Schematic
<img src="https://github.com/greglarious/TwinkleTie/blob/master/TwinkleTieSchematic.png?raw=true" width="500" height="500" />

## Parts List:
- One LED strip. 1m, 144LEDS. See notes below on differences and choosing.
  - [Adafruit NeoPixel 144/m strip](https://www.adafruit.com/product/1506)
  - [Adafruit NeoPixel 144/m mini skinny strip](https://www.adafruit.com/product/2970)
  - [generic brand WS2812 144/m strip](https://www.google.com/search?q=BTF-LIGHTING+WS2812B+144+LEDs) 
- [Adafruit Feather M0 Bluefruit LE](https://www.adafruit.com/product/2995)
- [2500mah 3.7v lion battery](https://www.adafruit.com/product/328)
- Ridiculous necktie

## Notes
- when choosing an LED strip, consider the waterproof rating, does it have a peel and stick backing, and how will it be mounted
  - IP30 rating means not waterproof. these usually come with a peel and stick backing
  - IP65 rating means waterproof to low pressure spray. These strips usually have a slightly rigid, curved, crystal clear silicone coating on one side and a peel and stick backing
  - IP67 rating means highly waterproof. These strips are usually inside a flexible rectangular silicone case that is not perfectly clear. I have never seen this form of LED strip with a peel and stick backing. Mounting is usually done with plastic brackets.
- Microcontrollers are usually available in 5V and 3V formats.
  - These LEDs technically require both 5V logic to control them and 5V power signal to illuminate
  - A board with 5V logic levels is a sure bet when driving WS2811 and WS2812 LEDs but in recent years I have had very good results with 3V controllers. 
  - In this project I am using a 3V controller and driving the illumination with only 3.7V. Having the battery voltage just 0.7v away from the driving voltage actually makes it more reliable and there is no noticeable sacrifice in brightness for driving it with 1.3V less than usual 
  
- When soldering to RGB LED strips, the joint can be fragile so it is very helpful to reinforce the solder locations with epoxy to provide durability
