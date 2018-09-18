#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "bitMaps.h" // stor


#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 4
#define BUTTON_4 5

#define LOW_BATTERY A2
#define TRIGGER A6
#define IR_SENSOR A7

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button1 = Bounce(BUTTON_1, 15);
Bounce button2 = Bounce(BUTTON_2, 15);
Bounce button3 = Bounce(BUTTON_3, 15);
Bounce button4 = Bounce(BUTTON_4, 15);

enum states {
  IDLE_STATE,
  PLAY_STATE,
  LOW_BAT_STATE
};

enum states deviceState = IDLE_STATE;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  matrix.begin(0x70); // I2C address for matrix
}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  if (button1.fallingEdge()) {
      matrix.clear();
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
      matrix.writeDisplay();
      deviceState = PLAY_STATE;
    } else if (button1.risingEdge()){
      matrix.clear();
      matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_RED);     
      matrix.writeDisplay();
      deviceState = IDLE_STATE;
    }

  switch (deviceState) {
    case IDLE_STATE:
      break;
    case PLAY_STATE:
      break;
    case LOW_BAT_STATE:
      break;
  }

}

