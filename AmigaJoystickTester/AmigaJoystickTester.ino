
#include <Wire.h>
#include "Joystick.h"
#include "DisplayManager.h"

// Pin definitions
const int pinUp = 5;
const int pinDown = 4;
const int pinLeft = 3;
const int pinRight = 2;
const int pinFire = 6;
const int pinFire2 =  7;

// Update display if there's a change
uint16_t  prevCurrentState = 0xFFFF; // Initialize to an invalid state
uint16_t  prevDetectedStates = 0xFFFF;


// Instantiate classes
Joystick joystick(pinUp, pinDown, pinLeft, pinRight, pinFire, pinFire2);
DisplayManager displayManager;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Setup started."));

  // Initialize joystick
  joystick.begin();
  Serial.println(F("Joystick initialized."));

  // Initialize display
  displayManager.begin();
  Serial.println(F("Display initialized."));

  // Show splash screen
  displayManager.showSplashScreen();

  Serial.println(F("Setup completed."));



}

void loop() {
  // Update joystick state
  joystick.update();

  // Get current and detected states
  uint16_t  currentState = joystick.getCurrentState();
  uint16_t  detectedStates = joystick.getDetectedStates();

  if (currentState != prevCurrentState || detectedStates != prevDetectedStates) {
    displayManager.updateDisplay(currentState, detectedStates);
    prevCurrentState = currentState;
    prevDetectedStates = detectedStates;
  }

  // Small delay to prevent excessive CPU usage
  delay(1);
}
