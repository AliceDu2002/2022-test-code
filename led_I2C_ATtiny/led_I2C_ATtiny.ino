// Code for the ATtiny85
#define I2C_SLAVE_ADDRESS 0x4 // Address of the slave
 
#include <TinyWireS.h>
#include "FastLED.h" 
#define NUM_LEDS 2
#define DATA_PIN PB4
#define BRIGHTNESS 32
#define LED1   PB3     // Test LED

int x, y, z = 0;
CRGB faya_colorSticker[NUM_LEDS];

// Gets called when the ATtiny receives an i2c request
void receiveEvent(uint8_t num_bytes)
{
  // should be 3 byte
//  if (num_bytes != 3){
//    digitalWrite(4, HIGH);
//    return;
//  }

  x = TinyWireS.receive();
  y = TinyWireS.receive();
  z = TinyWireS.receive();
  if(x == 0) {
    PORTB^= 1<<LED1;  
  }
  faya_colorSticker[0] = CRGB(x, y, z);
  FastLED.show(); 
  
}
 
void setup()
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(faya_colorSticker, NUM_LEDS);
//    FastLED.setBrightness(BRIGHTNESS);
    
//    TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
//    TinyWireS.onReceive(receiveEvent);
    // TinyWireS.onRequest(requestEvent);
    DDRB |= 1<<LED1;    
    PORTB |= 0<<LED1;                    // Turn PB1 off
    faya_colorSticker[0] = 0xFF0000;
    FastLED.show(); 
}
 
void loop()
{
    // This needs to be here
    // TinyWireS_stop_check();
      faya_colorSticker[0] = 0xFF0000;
      FastLED.show(); 
      delay(1000);
      PORTB^= 1<<LED1;  
      delay(2000);
//      faya_colorSticker[0] = CRGB(255, 0, 0);
//      FastLED.show(); 
//      faya_colorSticker[0] = CRGB(0, 0, 255);
//      FastLED.show(); 
}
