
#include <Wire.h>
#include "Joystick.h"
#include "DisplayManager.h"

// Pin definitions
const int pinUp = 2;
const int pinDown = 3;
const int pinLeft = 4;
const int pinRight = 5;
const int pinFire = 6;

// Update display if there's a change
uint16_t  prevCurrentState = 0xFFFF; // Initialize to an invalid state
uint16_t  prevDetectedStates = 0xFFFF;


// Instantiate classes
Joystick joystick(pinUp, pinDown, pinLeft, pinRight, pinFire);
DisplayManager displayManager;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started.");

  // Initialize joystick
  joystick.begin();
  Serial.println("Joystick initialized.");

  // Initialize display
  displayManager.begin();
  Serial.println("Display initialized.");

  // Show splash screen
  displayManager.showSplashScreen();

  Serial.println("Setup completed.");



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
