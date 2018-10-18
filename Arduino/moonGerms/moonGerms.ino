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
#include "states.h"
#include "globalVariables.h"

void setup() {
  Serial.begin(115200); // Initialize Serial port for communication with desktop app (eventually will also include midi?)
  matrix.begin(0x70); // Initialize display and set to blank
  matrix.clear();
  matrix.setRotation(1);
  matrix.drawBitmap(0, 0, emptyBMP, 8, 8, LED_RED);
  matrix.writeDisplay();

  updateCurrentAnimation(sawWaveBMP, animationLength); // set current animation to Saw
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  //Audio setup (see audioSetupFunctions tab)
  setupAudio();
  bootupAnimation();
}

void loop() {
  switch (deviceState) { // DEVICE IS FREE STANDING, NOT PLUGGED IN TO ANYTHING
    case STANDALONE_STATE:
      button1.update();
      button2.update();
      button3.update();
      button4.update();

      // See "inputChecks" tab for function details
      readButton1();   // Detect if Play button is pressed and play note
      readButton2();   // Detect waveform button for press and switch waveform type
      readButton3();  // Increase octave
      readButton4(); // Decrease Octave
      readIRSensor(); // Adjust pitch
      readTrigger(); // Adjust LP filter

      if (Serial.available()) { // check for incoming Serial data
        incomingData = Serial.readString();
      }
      if (incomingData == "CONNECT\n") { // if device received "CONNECT" from app, then switch to connect mode
        deviceState = CONNECTED_STATE;
        playAnimation = true;
        animationLength = plugBMPSize; //animation data stored in bitMaps.h
        updateCurrentAnimation(plugBMP, animationLength);
        currentFrame = 0;
      }
      break;

    case CONNECTED_STATE:

      button1.update(); // exit connection mode by pressing button 1
      if (button1.fallingEdge()) {
        deviceState = STANDALONE_STATE;
        incomingData = "";
        animationLength = sawWaveBMPSize; //animation data stored in bitMaps.h
        updateCurrentAnimation(sawWaveBMP, animationLength);
        currentFrame = 0;
        playAnimation = false;
      }

      if (Serial.available()) { // check for incoming Serial data
        incomingData = Serial.readStringUntil('\n');
        parameter = incomingData.substring(0, incomingData.indexOf(','));
        value = incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length());
        updateGlobalVariable(parameter, value);
        Serial.print(parameter.concat(value));
      }

      break;

    case CHARGING_STATE:
      break;
  }

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



