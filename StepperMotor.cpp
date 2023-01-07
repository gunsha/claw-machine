#include <MultiShiftRegister.h>
#include "StepperMotor.h"
StepperMotor::StepperMotor(int _sleepPin, int _stepPin, int _dirPin, int _stepDelayUs, MultiShiftRegister* _msr) {
  sleepPin = _sleepPin;
  stepPin = _stepPin;
  dirPin = _dirPin;
  stepDelayUs = _stepDelayUs;
  msr = _msr;
}
void StepperMotor::wake() {
  if (motorState) return;
  motorState = true;
  msr->set(sleepPin);
  msr->shift();
  delay(1);
}

void StepperMotor::sleep() {
  if (!motorState) return;
  motorState = false;
  msr->clear(sleepPin);
  msr->shift();
}
void StepperMotor::moveStepsShifter(int steps, bool direction) {
  if (direction) {
    msr->set(dirPin);
  } else {
    msr->clear(dirPin);
  }
  msr->shift();
  for (int i = 0; i < steps; i++) {
    msr->set(stepPin);
    msr->shift();
    delayMicroseconds(stepDelayUs);
    msr->clear(stepPin);
    msr->shift();
    delayMicroseconds(stepDelayUs);
  }
}

void StepperMotor::moveSteps(int steps, bool direction) {
  if (direction) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelayUs);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelayUs);
  }
}
void StepperMotor::forward() {
  moveStepsShifter(8, true);
}
void StepperMotor::backward() {
  moveStepsShifter(8, false);
}