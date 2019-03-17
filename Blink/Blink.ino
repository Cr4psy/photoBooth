//**************************************************************//
//  Name    : s[hotoBooth
//  Author  : Sofia Navarro Heredia, Anthony Clerc 
//  Date    : 17 Mar 2019   
//  Modified: 23 Mar 2010                                 
//  Version : 0.1                                             
//  Notes   : Code to run a photo booth with 16 LEDS, a camera  //
//            shutter and a start button
//****************************************************************

#include "LEDArray.cpp"



void setup() {
  //set pins to output so you can control the shift register
  Serial.begin(9600);
 // ledArray();

}
void loop() {

byte whichLED = 0x00;
for(size_t i = 0; i <8; i++)
{
  whichLED = (whichLED << 1) + 0b01;
  
  delay(300);
}

}



SIGNAL(TIMER0_COMPA_vect) 
{
 


} 

