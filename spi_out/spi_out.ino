/*  SPI Master Demo written by Robert Mollik, 2016
 *  
 *  This demo uses the SPI protocol on a Arduino Uno R3 / ATmega8 controller
 *  
 *  The demo sends out a request ID depending, whether a temperature or humidity signal shall be obtained from the slave. Both signals 
 *  are datatype float, however get received as 4 bytes and need to be re-assembled.
 */


#define CS PC0                      // Chip select pin, any vacant portpin can be used

float temp,hum;                     // Variables for the temperature and humidity, which will be recieved.

void initSPI(){

  // initilize the SPI functionalities on the ATmega
  
  DDRB  |= 1<<DDB2;                 // SS Pin has to be an output!!!! 1 means output and 0 means input
  PORTB |= 1<<PB2;                  // SS Pin set to HIGH so that a connected Pin would deselected
  
  
  SPCR  |= (1<<MSTR);               // Enable Master role, SPI Control register
  SPCR  |= (1<<SPE);                // Enable SPI, an register to enable SPI
  
  // To change the clock speed. See datasheet. I had to do this, with full speed I received a lot of wrong data.
  // Can be slowed down and expedited everywhere in the code. So the communication to slave A could be slow at 16 MHz and the 
  // communication to slave B fast with 2 MHz:
  SPCR  |= ((0<<SPR1) | (1<<SPR0));     

  // Define SCK, MOSI and custom CS as output
  DDRB |= ((1<SS) | (1<<DDB3) | (1<<DDB5));

}


float receiveFloat(const char reqID){

  float ans=0;                      // target variable for requested signal
  byte* ansPTR = (byte*)&ans;       // byte pointer on the target variable

  // Pull chip select pin down to tell slave that the communications starts
  PORTC &= ~(1<<CS);                // Take PC0(in define) in PC to high
  delayMicroseconds(20);            // Give the slave some time to digest

  
  // Send out the reqID
  SPDR = reqID;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)))
  delayMicroseconds(20);           // Give the slave some time to digest

//  // Receive 1st byte. The '11' is not considered from the slave, however this step is necessary to initiate the transmission.
//  SPDR = 11;                      
//  /* Wait for transmission complete */
//  while(!(SPSR & (1<<SPIF)))
//  ansPTR[0] = SPDR;                 // put the byte index 0 of the 'byte array' = float
//  delayMicroseconds(10);
//
//  
//  // Receive 2nd byte
//  SPDR = 11;
//  /* Wait for transmission complete */
//  while(!(SPSR & (1<<SPIF)))
//  ansPTR[1] = SPDR; 
//  delayMicroseconds(10);  
//
//  // Receive 3rd byte
//  SPDR = 11;
//  /* Wait for transmission complete */
//  while(!(SPSR & (1<<SPIF)))
//  ansPTR[2] = SPDR; 
//  delayMicroseconds(10);  
//
//  // Receive 4th byte
//  SPDR = 128;
//  /* Wait for transmission complete */
//  while(!(SPSR & (1<<SPIF)))
//  ansPTR[3] = SPDR; 
//  delayMicroseconds(10);    
  

  PORTC |= (1<<CS);             // Set chip select high and stop communication

  return ans;
}

void setup (void)
{
  Serial.begin(115200);         // Serial transmission for demonstration puroses
  
  initSPI();
  DDRC |= (1<<DDC0);            // datadrection for chip select is not in initSPI()
}  

void loop (void)
{
  temp = receiveFloat('T');     // See function definition
  Serial.print('T');
  delay(3000);
  hum = receiveFloat('H');
  Serial.print('H');
  delay(3000);

//  // Print in serial monitor for demonstration
//  Serial.print("T = ");
//  Serial.print(temp, DEC);
//  Serial.println();
//
//  Serial.print("H = ");
//  Serial.print(hum, DEC);
//  Serial.println(); 
//
//  delay(1000);
  
}  // end of loop
