//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 7;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

// MACRO
#define ALEN(a) (sizeof(a)/sizeof((a)[0]))

// LED_PATTERN gives the state of the pin of the 74HC595 in order to light the led 0-8 (0 being all led off)
byte LED_PATTERN[] = {0b00001111,0b10001101,0b01001101,0b00101101,0b00011101,0b10001110,0b01001110,0b00101110,0b00011110};

volatile byte whichLED;
void setup() {
  //set pins to output so you can control the shift register
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}
void loop() {

for(size_t i = 0; i <8; i++)
{
  whichLED = (whichLED << 1) + 0b01;
  delay(300);
}
whichLED = 0x00;

}


// Interrupt is called once a millisecond, to update the LEDs
volatile int i = 0;
volatile byte tmp;
SIGNAL(TIMER0_COMPA_vect) 
{
 
  i = i+1;
  if(i == 1){
    tmp = whichLED;
  }
  if((tmp & 0b01) == 0b01){
     writeByte(LED_PATTERN[i]);
  }
  tmp = tmp >> 1;
  if (i==8) {
    i=0;
  }

} 

void writeByte(byte b){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin,clockPin, LSBFIRST, b);
  digitalWrite(latchPin,HIGH);
}

