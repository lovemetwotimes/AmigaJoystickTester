#include "Joystick.h"

Joystick::Joystick(int upPin, int downPin, int leftPin, int rightPin, int firePin, int fire2Pin)
  : pinUp(upPin), pinDown(downPin), pinLeft(leftPin), pinRight(rightPin), pinFire(firePin), pinFire2(fire2Pin),
    currentState(0), detectedStates(0) {
}

void Joystick::begin() {
  pinMode(pinUp, INPUT_PULLUP);
  pinMode(pinDown, INPUT_PULLUP);
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);
  pinMode(pinFire, INPUT_PULLUP);
  pinMode(pinFire2, INPUT_PULLUP);
}

void Joystick::update() {
  currentState = 0;

  bool up = !digitalRead(pinUp);
  bool down = !digitalRead(pinDown);
  bool left = !digitalRead(pinLeft);
  bool right = !digitalRead(pinRight);
  bool fire = !digitalRead(pinFire);
  bool fire2 = !digitalRead(pinFire2);

  // Diagonal detection
  if (up && left) {
    currentState |= UP_LEFT_MASK;
  } else if (up && right) {
    currentState |= UP_RIGHT_MASK;
  } else if (down && left) {
    currentState |= DOWN_LEFT_MASK;
  } else if (down && right) {
    currentState |= DOWN_RIGHT_MASK;
  } else {
    // Only set individual directions if no diagonals are detected
    if (up) currentState |= UP_MASK;
    if (down) currentState |= DOWN_MASK;
    if (left) currentState |= LEFT_MASK;
    if (right) currentState |= RIGHT_MASK;
  }
  
  if (fire) currentState |= FIRE_MASK;
  if (fire2) currentState |= FIRE2_MASK;

  // Update detected states
  detectedStates |= currentState;
}

void Joystick::reset() {
  detectedStates = 0;
}

uint16_t  Joystick::getCurrentState() {
  return currentState;
}

uint16_t  Joystick::getDetectedStates() {
  return detectedStates;
}
