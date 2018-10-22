// Animates Title and Sinewave during bootup
void bootupAnimation() {
  for (int i = 0; i < 8; i++) {
    matrix.clear();
    matrix.drawBitmap(0, 0, moonGermsBMP[i], 8, 8, LED_RED);
    matrix.writeDisplay();
    delay(80);
  }
  for (int i = 8; i < 18; i++) {
    matrix.clear();
    matrix.drawBitmap(0, 0, moonGermsBMP[i], 8, 8, LED_GREEN);
    matrix.writeDisplay();
    delay(80);
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
void updateCurrentAnimation(int bank) {
  for (int i = 0; i < 22; i ++) {
    for (int j = 0; j < 8; j++) {
      switch (bank) {
        case 0:
          currentAnimation[i][j] = sawWaveBMP[i][j];
          animationLength = sawWaveBMPSize;
          break;
        case 1:
          currentAnimation[i][j] = squareWaveBMP[i][j];
          animationLength = squareWaveBMPSize;
          break;
        case 2:
          currentAnimation[i][j] = sawWaveReverseBMP[i][j];
          animationLength = sawWaveReverseBMPSize;
          break;
        case 3:
          currentAnimation[i][j] = triangleWaveBMP[i][j];
          animationLength = triangleWaveBMPSize;
          break;
      }
    }
  }
  displayColor = DisplayColor[bank];
  currentFrame = 0;
}

void updateAnimationConnect() {
  for (int i = 0; i < 22; i ++) {
    for (int j = 0; j < 8; j++) {
      currentAnimation[i][j] = plugBMP[i][j];
      animationLength = plugBMPSize;
    }
  }
  displayColor = LED_YELLOW;
  currentFrame = 0;
}

