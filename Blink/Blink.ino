//**************************************************************//
//  Name    : s[hotoBooth
//  Author  : Sofia Navarro Heredia, Anthony Clerc 
//  Date    : 17 Mar 2019   
//  Modified: 23 Mar 2010                                 
//  Version : 0.1                                             
//  Notes   : Code to run a photo booth with 16 LEDS, a camera  //
//            shutter and a start button
//****************************************************************

#include <LEDArray.h>
#define NB_LEDS 8
LEDArray ledArray;

void setup() {
  //set pins to output so you can control the shift register
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  digitalWrite(0,LOW);
  pinMode(5,INPUT);

  ledArray.setNbLEDs(NB_LEDS);

}
void loop() {

if(digitalRead(5)){

byte ledState = 0x00;
for(size_t i = 0; i <NB_LEDS; i++)
{
  ledState = (ledState << 1) + 0b01;
  ledArray.setLedsState(ledState);
  delay(300);
}
digitalWrite(0,HIGH);
delay(100);
digitalWrite(0,LOW);
delay(100);
digitalWrite(0,HIGH);
delay(100);
digitalWrite(0,LOW);
}

}



SIGNAL(TIMER0_COMPA_vect) 
{
  ledArray.ledCycle();
 


} 

