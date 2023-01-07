
#include <MultiShiftRegister.h>
#include "StepperMotor.h"
MultiShiftRegister *msr;
StepperMotor *motorX;
StepperMotor *motorY;
//shift stepper X
#define dirPinX 0
#define stepPinX 1
#define sleepPinX 2
//shift stepper Y
#define dirPinY 3
#define stepPinY 4
#define sleepPinY 5

//Pin connected to latch pin 12 (ST_CP) of 74HC595
#define latchPin 8
//Pin connected to clock pin 11 (SH_CP) of 74HC595
#define clockPin 12
////Pin connected to Data in 14 (DS) of 74HC595
#define dataPin 11

#define useShiftRegister

// when not using shift register
void setupStepper() {
  //X
  pinMode(stepPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(sleepPinX, OUTPUT);
  digitalWrite(sleepPinX, LOW);
  //Y
  pinMode(stepPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(sleepPinY, OUTPUT);
  digitalWrite(sleepPinY, LOW);
}

void setupShifter() {
  msr = new MultiShiftRegister(1, latchPin, clockPin, dataPin);
  digitalWrite(latchPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, HIGH);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //OE
  //pinMode(A0, OUTPUT);

  for (int a = 0; a < 8; a++) {
    msr->clear(a);
    msr->shift();
  }

  //digitalWrite(A0,LOW);
}

void setup() {
  pinMode(10, OUTPUT);
  #ifndef useShiftRegister
  setupStepper();
  #endif

  #ifdef useShiftRegister
  setupShifter();
  #endif

  motorX = new StepperMotor(sleepPinX, stepPinX, dirPinX, 1000, msr);
  motorY = new StepperMotor(sleepPinY, stepPinY, dirPinY, 1000, msr);
  setupButtons();
  Serial.begin(9600);
}

void loop() {
  //loopMusic();
  checkButtons();
}
