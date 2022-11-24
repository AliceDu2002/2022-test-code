/*  USI SPI Slave Demo written by Robert Mollik, 2016
 *  
 *  This demo uses the SPI protocol with USI interface. This is necessary with with the smaller AVR controller since they don't 
 *  a complete SPI functionality. 
 *  Demo is written for the pinout of an Arduino Trinket and ATtiny85. Pins need to be modified if a different controller is used.
 *  
 *  The demo takes receives a request ID from the Master at the beginning of every communication. According to the request ID,
 *  it sends back either a temperature or a humidity values. Since both values are present in float, the 4 bytes of the float need
 *  to be send separately.
 */

#define CS    PB3     // Chip select
#define LED1   PB4     // Test LED
#define LED2    PB1     // MISO or Data Out
#define USCK  PB2     // Clock

// Variable use in Interrupt need to be volotile to tell the compiler, they may be altered in other functions than in Main loop.
// Otherwise the compiler could remove or replace them with a constant:

volatile char reqID = 0;              // This is for the first byte we receive, which is intended to be the request identifier
volatile uint8_t index = 0;           // this is to send back the right element in the array

// Test variables:

float temperature = 34.3;
float humidity = 87.5;

// Pointer on the test variables. Datatype is casted into byte to read out the single bytes of the float:

byte * tempPTR = (byte*) &temperature;
byte * humPTR  = (byte*) &humidity;

void setup (void)
{
  cli();                              // Deactivate Interrupts
  
  DDRB |= 1<<LED1;    
  DDRB |= 1<<LED2;    // Set PB1 as output (LED on Trinket) / PB0 will be the Input for the Interrupt
  // DDRB |= 1<<DO;                      // MISO Pin has to be an output

  USICR = ((1<<USIWM0)|(1<<USICS1));  // Activate 3- Wire Mode and use of external clock but NOT the interrupt at the Counter overflow (USIOIE)
  
  PORTB |= 0<<LED1;                    // Turn PB1 off
  PORTB |= 0<<LED2;                    // Turn PB1 off
  PORTB |= 1<<CS;                     // Activate Pull-Up resistor on PB0
  
  PCMSK|=1<<CS;                       // Active Interrupt on PB1
  GIMSK|=1<<PCIE;                     // General Interrupt Mask Register / PCIE bit activates external interrupts

  delay(500);

  sei();                              // Activate Interrupts
}  // end of setup


// Interrupt routine at the CS pin. Always executed when value on CS pin changes:

ISR(PCINT0_vect)
  {    
    if((PINB & (1<<CS))== 0){
      
      // If edge is falling, the command and index variables shall be initialized
      // and the 4-bit overflow counter of the USI communication shall be activated:

      reqID = 0;
      index = 0;
      USICR |= (1<<USIOIE);
      USISR = 1<<USIOIF;      // Clear Overflow bit

      // XOR operation to turn PB3 (LED) on/off. (Not needed for USI)
      
      // PORTB^= 1<<LED1;  
    }
    else{

      // If edge is rising, turn the 4-bit overflow interrupt off:
      
      USICR &= ~(1<<USIOIE);
    }
  }

 // USI interrupt routine. Always executed when 4-bit overflows (after 16 clock edges = 8 clock cycles):

ISR(USI_OVF_vect)
  {  
      switch(reqID){

        // Switch-Case to respond according to request from Master:

        case 0:               // If reqID value is zero (just initialized), then first message is the reqID.

          reqID = USIDR;      // Read in from USIDR register
          USISR = 1<<USIOIF;  // Clear Overflow bit
          
        case 'T':
          PORTB^= 1<<LED1;  
//          // Write value to send back into USIDR and clear the overflow bit:
//          USIDR = tempPTR[index];
//          USISR = 1<<USIOIF;       
//          index++;            // Increment index to transmit the folloing element next
          break;
          
        case 'H':
          PORTB^= 1<<LED2;  
          // Write value to send back into USIDR and clear the overflow bit:
//          USIDR = humPTR[index]; 
//          USISR = 1<<USIOIF; 
//          index++;            // Increment index to transmit the folloing element next
          break;

        default:
          // Default option of Switch-Case. Send 'reqID' back for debugging.
          USIDR = reqID;
          USISR = 1<<USIOIF;
          
      }      
  }

void loop (void)
{
  // Nothing done here in this example
}  
