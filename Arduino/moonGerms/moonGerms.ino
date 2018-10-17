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

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button4 = Bounce(BUTTON_1, 15);
Bounce button3 = Bounce(BUTTON_2, 15);
Bounce button2 = Bounce(BUTTON_3, 15);
Bounce button1 = Bounce(BUTTON_4, 15);

int waveformType = WAVEFORM_SAWTOOTH; // default waveform on both oscillators
uint8_t currentAnimation[22][8];// 20 frame array to hold animations
int animationLength = sawWaveBMPSize; // computes number of frames of selected animation
int currentFrame = 0;
int frameRate = 50; // milliseconds between each frame
int lastMillis = 0; //time elapsed since previous frame
int displayColor = LED_RED;
boolean playAnimation = false;

int triggerRead;

const int numReadings = 300; // Number of samples to average for IR sensor reading
int infraredReadings[numReadings]; // Array containing samples of IR readings
int readIndex = 0;
float readingAverage;
float mappedAverage;

int octaveCounter = 4;
float centerFreq = noteA[octaveCounter]; // set global frequency to A3
float globalFreq = centerFreq; // actual frequency being generated, dependent on IR sensor (bendFactor) and octave
float bendFactor;
float globalGain;
float detune = 1.0;

String incomingData = "";

enum states deviceState = STANDALONE_STATE;

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
  Serial.println(WAVEFORM_SAWTOOTH);
  Serial.println(WAVEFORM_SAWTOOTH_REVERSE);
  Serial.println(WAVEFORM_SQUARE);
  Serial.println(WAVEFORM_TRIANGLE);
  Serial.println(WAVEFORM_SINE);
  Serial.println("");
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



