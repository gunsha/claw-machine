#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5

bool btn1State = false;
bool btn2State = false;
bool btn3State = false;
bool btn4State = false;

bool btn1PrevState = false;
bool btn2PrevState = false;
bool btn3PrevState = false;
bool btn4PrevState = false;

void setupButtons() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
}

bool buttonPressed(int btn) {
  return digitalRead(btn) == LOW;
}

void moveAxis(bool state1, bool prevState1, bool state2, bool prevState2, StepperMotor* motor) {
  if (state1 && !state2) {
    if (state1 && !prevState1) {
      motor->wake();
    }
    motor->forward();
  }
  if (state2 && !state1) {
    if (state2 && !prevState2) {
      motor->wake();
    }
    motor->backward();
  }
  if ((prevState1 && !state1) || (prevState2 && !state2)) {
    motor->sleep();
  }
}

void checkButtons() {
  btn1State = buttonPressed(btn1);
  btn2State = buttonPressed(btn2);
  btn3State = buttonPressed(btn3);
  btn4State = buttonPressed(btn4);

  moveAxis(btn1State, btn1PrevState, btn2State, btn2PrevState, motorX);
  moveAxis(btn3State, btn3PrevState, btn4State, btn4PrevState, motorY);

  btn1PrevState = btn1State;
  btn2PrevState = btn2State;
  btn3PrevState = btn3State;
  btn4PrevState = btn4State;
}