#ifndef StepperMotor_h
#define StepperMotor_h
#include <Arduino.h>
class StepperMotor {
private:
  bool motorState;
  int sleepPin;
  int stepPin;
  int dirPin;
  int stepDelayUs;
  MultiShiftRegister* msr;

public:
  StepperMotor(int _sleepPin, int _stepPin, int _dirPin, int _stepDelayUs, MultiShiftRegister* _msr);
  void wake();
  void sleep();
  void moveStepsShifter(int steps, bool direction);
  void moveSteps(int steps, bool direction);
  void forward();
  void backward();
};

#endif
