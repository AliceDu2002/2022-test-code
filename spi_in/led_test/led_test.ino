#include <Wire.h> // Library for I2C communication
#include <FastLED.h>

#define DATA_PIN 11
#define BRIGHTNESS 255
int num_leds = 30;
int32_t colors[6]={0xFF0000,0x00FF00, 0x0000FF, 0xFF0000,0x00FF00, 0x0000FF};
CRGB leds[35];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, 300);
  for(int i=0;i<num_leds;i++){
    leds[i] = CRGB::Black;
   }
  FastLED.show();
  Serial.begin(9600);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0;i < num_leds; i++){
    leds[i] = colors[i % 3];
    if(i % 3 == 0) {
      leds[i] = CRGB::Red;
    }
    else if(i % 3 == 1) {
      leds[i] = CRGB::Green;
    }
    else {
      leds[i] = CRGB::Blue;
    }
    if(i > 11) {
      if(i % 3 == 0) {
        leds[i] = 0xFF0000;
      }
      else if(i % 3 == 1) {
        leds[i] = 0x00FF00;
      }
      else {
        leds[i] = 0x0000FF;
      }
    }
  }
  FastLED.show();
  delay(3000);
}
