
#include "Arduino.h"


class LEDArray
{
private:
    // LED_PATTERN gives the state of the pin of the 74HC595 in order to light the led 0-8 (0 being all led off)
    const byte LED_PATTERN[9] = {0b00001111,0b10001101,0b01001101,0b00101101,0b00011101,0b10001110,0b01001110,0b00101110,0b00011110};
    // Interrupt is called once a millisecond, to update the LEDs
    volatile int cycleCount = 0;
    volatile byte ledsOn;
    volatile byte ledsOnPrev;

    // 74HC595 Connections
    //ST_CP
    int latchPin = 7;
    //SH_CP
    int clockPin = 12;
    //DS
    int dataPin = 11;



    void writeByte(byte b);

public:
  LEDArray();
  void ledLighting();
  void setLedsOn(byte);
};

// Constructor
LEDArray::LEDArray()
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function below
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
}


void LEDArray::setLedsOn(byte on){
    ledsOn = on;
}

void LEDArray::writeByte(byte b){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin,clockPin, LSBFIRST, b);
  digitalWrite(latchPin,HIGH);
}

void LEDArray::ledLighting(){
    cycleCount = cycleCount+1;
    if(cycleCount == 1){
        ledsOnPrev = ledsOn;
    }
    if((ledsOnPrev & 0b01) == 0b01){
        writeByte(LED_PATTERN[cycleCount]);
    }
    ledsOnPrev = ledsOnPrev >> 1;
    if (cycleCount==8) {
        cycleCount=0;
    }
}