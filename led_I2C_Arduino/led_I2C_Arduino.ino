#include <Wire.h>

#define SLAVE_ADDRESS 0x12
#define SERIAL_BAUD 57600 

 
void setup()
{
  Wire.begin();
 
  Serial.begin(SERIAL_BAUD);
  Serial.println("I2C Master.02 started");
  Serial.println();
}
 
 
void loop()
{
//  Serial.print("send message to " + SLAVE_ADDRESS + '\n');
//  if (Serial.available()) {
//    Serial.print("serial available " + SLAVE_ADDRESS + '\n');
    Wire.beginTransmission(SLAVE_ADDRESS);
//    while(Serial.available()) {
//      Wire.write(Serial.read());
//      delay(1);
//    }
    for(int i = 0; i < 50; i++) {
      Wire.write(1);
      delay(1);
    }
    Wire.endTransmission();

    delay(100);
  }
//#include <Wire.h>
//
//void setup()
//{
//  
//  Wire.begin(); // join i2c bus (address optional for master)
//  Wire.setClock(400000L);
//  Serial.begin(9600);
//}
//
//void loop()
//{
//    Wire.beginTransmission(0x12);
//    Wire.write(0);
//    Wire.write(0);
//    Wire.write(0);
//    Serial.print("0\n");
//    Wire.endTransmission();
//  
//    delay(1);
//  
//    Wire.beginTransmission(0x12);
//    Wire.write(200);
//    Wire.write(200);
//    Wire.write(200);
//    Serial.print("200\n");
//    Wire.endTransmission();
//  
//    delay(50);
//  for(int i = 0; i < 5; i++) {
//    Wire.beginTransmission(0x04);
//    if(i%3 == 0) {
//      Wire.write(255);
//      Wire.write(0);
//      Wire.write(0);
//      Serial.print("0\n");
//      
//    }
//    else if(i%3 == 1) {
//      Wire.write(0);
//      Wire.write(255);
//      Wire.write(0);
//      Serial.print("1\n");
//    }
//    else{
//      Wire.write(0);
//      Wire.write(0);
//      Wire.write(255);
//      Serial.print("2\n");      
//    }
//    Wire.endTransmission();
//    delay(1);
//  }
  // delay(1000);
//}
