# TwinkleTie
Arduino code for runnng an RGB LED light show on a holiday necktie.
TL/DR: Rudolph with your tie so bright, turn that thing down before you harm someone's retina.

## Demonstration
https://youtu.be/MoQlWXUC1UQ

## Parts List:
- Two 15 LED WS2811 strips
- Arduino Mini (or equivalent) 
- Small USB battery
- Ridiculous necktie

## Notes
- Controllers with 5V logic levels are safest unless you have tested your LED strips with 3V
- Even if your 3V controller works with 1 LED strip, it might not work with 2.  Chain the strips together and use 1 data pin to fix this.
- When soldering to RGB LED strips, the joint can be fragile so it is very helpful to reinforce the solder locations with epoxy to provide durability
