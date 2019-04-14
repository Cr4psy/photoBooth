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
#include "pitches.h"

#define NB_LEDS 16
#define SPEAKER_PIN 11
#define CAMERA_FOCUS_PIN 12
#define CAMERA_SHUTTER_PIN 13
#define BUTTON_PIN A0

LEDArray ledArray;

void setup() {
  //set pins to output so you can control the shift register
  Serial.begin(9600);
  pinMode(CAMERA_FOCUS_PIN, OUTPUT);
  pinMode(CAMERA_SHUTTER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  
  ledArray.setNbLEDs(NB_LEDS);
  ledArray.setLedsState(0);

}
void loop() {


 if (fallingEdge(BUTTON_PIN) || true){

    uint16_t ledState = 0x00;
    for(size_t i = 0; i <NB_LEDS; i++)
    {
      ledState = (ledState >> 1) + (0b01<<(NB_LEDS-1));
      ledArray.setLedsState(leftRotate(ledState,1));
      
      if ((i+1)%5==0) {
        tone(SPEAKER_PIN,NOTE_A3);
      }

      delay(200);
      noTone(SPEAKER_PIN);
    }
    ledArray.setLedsState(0);
    delay(600);
    ledArray.setLedsState(0xFFFF);
    tone(SPEAKER_PIN, NOTE_A4);
    photo();
    noTone(SPEAKER_PIN);
    ledArray.setLedsState(0);
  }

}


bool fallingEdge(uint8_t pin){
  if (digitalRead(pin) == LOW) {
    delay(10);
    return !digitalRead(pin);
  }
  return false;
}

// photo trigger a photo shoot 
// Both the focus and the shutter need to be set high to take a photo
// It works in bulb mode which means that the first tigger start the shoot 
// the second trigger stop the shoot.
void photo(){
  digitalWrite(CAMERA_FOCUS_PIN, HIGH);
  digitalWrite(CAMERA_SHUTTER_PIN, HIGH);
  delay(100);
  digitalWrite(CAMERA_FOCUS_PIN, LOW);
  digitalWrite(CAMERA_SHUTTER_PIN, LOW);

  delay(200);
  
  digitalWrite(CAMERA_FOCUS_PIN, HIGH);
  digitalWrite(CAMERA_SHUTTER_PIN, HIGH);
  delay(100);
  digitalWrite(CAMERA_FOCUS_PIN, LOW);
  digitalWrite(CAMERA_SHUTTER_PIN, LOW);
  return;
  
}

uint16_t leftRotate(uint16_t n, unsigned int d) 
{ 
   return (n << d)|(n >> (16 - d)); 
} 

int rightRotate(int n, unsigned int d) 
{ 
   return (n >> d)|(n << (16 - d)); 
} 

volatile int I = 0;
SIGNAL(TIMER0_COMPA_vect) 
{
   ledArray.ledCycle();
} 

