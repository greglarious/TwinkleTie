# TwinkleTie
Arduino code for runnng an RGB LED light show on a holiday necktie.
TL/DR: Rudolph with your tie so bright, turn that thing down before you harm someone's retina.

## Demonstration
[![Demonstration Video](https://i.ytimg.com/vi/MoQlWXUC1UQ/0.jpg)](https://youtu.be/MoQlWXUC1UQ)

## Schematic
<img src="https://github.com/greglarious/TwinkleTie/blob/master/TwinkleTieSchematic.png?raw=true" width="500" height="500" />

## Parts List:
- Two 15 LED [WS2811 strips](https://www.google.com/search?q=ws2812+led+strip)
- [Arduino Mini 5v](https://www.google.com/search?q=arduino+mini+pro+5v) - or equivalent 5v logic controller 
- [Slim USB battery](https://www.google.com/search?q=ultra-slim+usb+battery). The video shows an 80g round battery but that is a bit lumpy to wear. There are 60g flat batteries that would look and feel much better.
- Ridiculous necktie

## Notes
- Controllers with 5V logic levels are safest unless you have tested your LED strips with 3V
- Even if your 3V controller works with 1 LED strip, it might not work with 2.  Chain the strips together and use 1 data pin to fix this.
- When soldering to RGB LED strips, the joint can be fragile so it is very helpful to reinforce the solder locations with epoxy to provide durability
