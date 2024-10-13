#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>

// Constants for joystick bit masks
#define UP_MASK         0x01
#define DOWN_MASK       0x02
#define LEFT_MASK       0x04
#define RIGHT_MASK      0x08
#define FIRE_MASK       0x10
#define UP_LEFT_MASK    0x20
#define UP_RIGHT_MASK   0x40
#define DOWN_LEFT_MASK  0x80
#define DOWN_RIGHT_MASK 0x100


class Joystick {
  public:
    // Constructor
    Joystick(int upPin, int downPin, int leftPin, int rightPin, int firePin);

    // Methods
    void begin();
    void update();
    void reset();
    uint16_t  getCurrentState();
    uint16_t  getDetectedStates();

  private:
    // Pin definitions
    int pinUp;
    int pinDown;
    int pinLeft;
    int pinRight;
    int pinFire;

    // Current and detected states (bit masks)
    uint16_t currentState;
    uint16_t detectedStates;
};


#endif