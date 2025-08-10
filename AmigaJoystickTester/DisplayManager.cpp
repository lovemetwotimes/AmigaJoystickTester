#include "DisplayManager.h"

const int smallSquareSize = 2; // Size of the small square

DisplayManager::DisplayManager()
  : u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE) {
}

void DisplayManager::begin() {
  u8g2.begin();
}

void DisplayManager::showSplashScreen() {
  u8g2.clearBuffer();

  // Draw inverted headline background
  u8g2.setDrawColor(1); // Set draw color to white
  u8g2.drawBox(0, 0, 128, 12); // Draw black rectangle for inverted text

  u8g2.setDrawColor(0); // Set draw color to black for inverted text
  u8g2.setFont(u8g2_font_6x12_tr); // Set font with height approximately 12 pixels

  // Center the text horizontally
  const char* headline = "JT";
  int16_t textWidth = u8g2.getStrWidth(headline);
  int16_t textX = (128 - textWidth) / 2;
  u8g2.setCursor(textX, 10); // y position adjusted to fit within 12 pixels
  u8g2.print(headline);

  u8g2.sendBuffer();
  //delay(2000);
}

void DisplayManager::updateDisplay(uint16_t currentState, uint16_t detectedStates) {
  u8g2.clearBuffer();

  // Draw inverted headline
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, 128, 12);
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_6x12_tr);
  const char* headline = "JT";
  int16_t textWidth = u8g2.getStrWidth(headline);
  int16_t textX = (128 - textWidth) / 2;
  u8g2.setCursor(textX, 10);
  u8g2.print(headline);

  // Set draw color back to normal for the rest
  u8g2.setDrawColor(1);

  // Box dimensions and positions
  const int boxSize = 16; // 16x16 pixels
  const int spacing = 2;  // 2 pixels spacing
  const int xStart = 0;   // Left-aligned
  const int yStart = 12;  // Start after headline

  // Map of positions for each box
  struct Box {
    int x;
    int y;
    uint16_t mask;
  };

  Box boxes[9] = {
    // First row (Up-Left, Up, Up-Right)
    { xStart + (boxSize + spacing) * 0, yStart + (boxSize + spacing) * 0, UP_LEFT_MASK },
    { xStart + (boxSize + spacing) * 1, yStart + (boxSize + spacing) * 0, UP_MASK },
    { xStart + (boxSize + spacing) * 2, yStart + (boxSize + spacing) * 0, UP_RIGHT_MASK },

    // Second row (Left, Fire, Right)
    { xStart + (boxSize + spacing) * 0, yStart + (boxSize + spacing) * 1, LEFT_MASK },
    { xStart + (boxSize + spacing) * 1, yStart + (boxSize + spacing) * 1, FIRE_MASK },
    { xStart + (boxSize + spacing) * 2, yStart + (boxSize + spacing) * 1, RIGHT_MASK },

    // Third row (Down-Left, Down, Down-Right)
    { xStart + (boxSize + spacing) * 0, yStart + (boxSize + spacing) * 2, DOWN_LEFT_MASK },
    { xStart + (boxSize + spacing) * 1, yStart + (boxSize + spacing) * 2, DOWN_MASK },
    { xStart + (boxSize + spacing) * 2, yStart + (boxSize + spacing) * 2, DOWN_RIGHT_MASK }
  };

  // Draw boxes with three states
  for (int i = 0; i < 9; i++) {
    int x = boxes[i].x;
    int y = boxes[i].y;
    uint16_t mask = boxes[i].mask;

    if (currentState & mask) {
      // State 2: Currently active - Draw filled box
      u8g2.drawBox(x, y, boxSize, boxSize);
    } else if (detectedStates & mask) {
      // State 3: Seen but not active - Draw thicker rim facing inward
      u8g2.drawFrame(x, y, boxSize, boxSize);
      u8g2.drawFrame(x + 1, y + 1, boxSize - 2, boxSize - 2);
      u8g2.drawFrame(x + 2, y + 2, boxSize - 4, boxSize - 4);
      int centerX = x + (boxSize - smallSquareSize) / 2;
      int centerY = y + (boxSize - smallSquareSize) / 2;
      u8g2.drawBox(centerX, centerY, smallSquareSize, smallSquareSize);
    } else {
      // State 1: Never seen - Draw normal frame
      u8g2.drawFrame(x, y, boxSize, boxSize);
    }
  }

  // Display current values
  u8g2.setFont(u8g2_font_8x13_tr);
  int textPosX = xStart + (boxSize + spacing) * 3 + 5; // Position to the right of the boxes
  int textPosY = yStart + 12; // Start below the headline

  u8g2.setCursor(textPosX, textPosY);
  u8g2.print("Current");

  textPosY += 14;
  u8g2.setCursor(textPosX, textPosY);

  if (currentState & UP_MASK) u8g2.print(F("Up "));
  if (currentState & DOWN_MASK) u8g2.print(F("Down "));
  if (currentState & LEFT_MASK) u8g2.print(F("Left "));
  if (currentState & RIGHT_MASK) u8g2.print(F("Right "));
  if (currentState & UP_LEFT_MASK) u8g2.print(F("Up+L "));
  if (currentState & UP_RIGHT_MASK) u8g2.print(F("Up+R "));
  if (currentState & DOWN_LEFT_MASK) u8g2.print(F("Down+L "));
  if (currentState & DOWN_RIGHT_MASK) u8g2.print(F("Down+R "));

  textPosY += 14;
  u8g2.setCursor(textPosX, textPosY);
  if (currentState & FIRE_MASK) u8g2.print(F("Fire "));
  textPosY += 14;
  if (currentState & FIRE2_MASK) u8g2.print(F("Fire2"));



  u8g2.sendBuffer();
}
