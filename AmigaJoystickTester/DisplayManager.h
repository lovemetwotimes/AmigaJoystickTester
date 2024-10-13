#ifndef DisplayManager_h
#define DisplayManager_h

#include <Arduino.h>
#include <U8g2lib.h>

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

class DisplayManager {
  public:
    // Constructor
    DisplayManager();

    // Methods
    void begin();
    void showSplashScreen();
    void updateDisplay(uint16_t  currentState, uint16_t  detectedStates);

  private:
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;
};

#endif