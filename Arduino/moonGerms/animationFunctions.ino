// Animates Title and Sinewave during bootup
void bootupAnimation() {
  for (int i = 0; i < 8; i++) {
    matrix.clear();
    matrix.drawBitmap(0, 0, moonGermsBMP[i], 8, 8, LED_RED);
    matrix.writeDisplay();
    delay(120);
  }
  for (int i = 8; i < 18; i++) {
    matrix.clear();
    matrix.drawBitmap(0, 0, moonGermsBMP[i], 8, 8, LED_GREEN);
    matrix.writeDisplay();
    delay(120);
  }
  for (int i = 0; i < 8; i++) {
    matrix.clear();
    matrix.drawBitmap(0, 0, sineWaveBMP[i], 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(100);
  }
  for (int i = 6; i > -1; i--) {
    matrix.clear();
    matrix.drawBitmap(0, 0, sineWaveBMP[i], 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    delay(100);
  }
}


// Assigns new animation to "currentAnimation" array
void updateCurrentAnimation(uint8_t newAnimation[][8], int animationLength) {
  for (int i = 0; i < animationLength; i ++) {
    for (int j = 0; j < 8; j++) {
      currentAnimation[i][j] = newAnimation[i][j];
    }
  }
}
