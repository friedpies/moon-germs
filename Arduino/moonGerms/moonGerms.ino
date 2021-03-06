// Moon Germs Handheld Synthesizer
// V0.1 Arduino Code, October 2018
// By Kenneth Marut (www.kennethmarut.com)
//
// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "pinDefines.h"
#include "audioConnections.h"
#include "bitMaps.h"
#include "aLookup.h"
#include "globalVariables.h"

void setup() {
  delay(2000); // safety
  Serial.begin(115200); // Initialize Serial port for communication with desktop app (eventually will also include midi?)
  matrix.begin(0x70); // Initialize display and set to blank
  matrix.clear();
  matrix.setRotation(1);
  matrix.drawBitmap(0, 0, emptyBMP, 8, 8, LED_RED);
  matrix.writeDisplay();

  updateCurrentAnimation(bank); // set current animation to Saw
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  SPI.setMOSI(SDCARD_MOSI_PIN); // set up SD. Will eventually use to store bank data
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  //Audio setup (see audioSetupFunctions tab)
  setupAudio();
  bootupAnimation();
}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  // See "inputChecks" tab for function details
  readButton1();   // Detect if Play button is pressed or if "pressPlay" is received from App, and play note
  readButton2();   // Detect waveform button for press and switch waveform type
  readButton3();  // Increase octave
  readButton4(); // Decrease Octave
  readTrigger(); // Read input from trigger
  readIRSensor(); // Adjust pitch

  if (playAnimation) {
    if ((millis() - lastMillis) > frameRate) {
      if (currentFrame == animationLength) {
        currentFrame = 0;
      }
      matrix.clear();
      matrix.drawBitmap(0, 0, currentAnimation[currentFrame], 8, 8, displayColor);
      matrix.writeDisplay();
      currentFrame++;
      lastMillis = millis();
    }
  }
}



