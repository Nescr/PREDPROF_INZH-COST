#include <Adafruit_NeoPixel.h>

#define PIN        6 

#define NUMPIXELS 19 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  pixels.begin();
}

void loop() {
  pixels.clear();
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.show();
}