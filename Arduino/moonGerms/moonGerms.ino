#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "pinDefines.h"
#include "states.h"
#include "audioConnections.h"
#include "bitMaps.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button1 = Bounce(BUTTON_1, 15);
Bounce button2 = Bounce(BUTTON_2, 15);
Bounce button3 = Bounce(BUTTON_3, 15);
Bounce button4 = Bounce(BUTTON_4, 15);

int waveform_type = WAVEFORM_SINE;
int triggerRead;
int infraredRead;
int globalFreq;
float globalGain;
;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  mixer1.gain(0, 0.7);

  matrix.begin(0x70); // I2C address for matrix
}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();
 
  checkButton1();
  checkButton2();

  switch (deviceState) {
    case IDLE_STATE:
      break;
    case PLAY_STATE:
    // read linear pot and check for value change, adjust mixer gain 
      if (globalGain != checkTrigger()){
        globalGain = checkTrigger();
        mixer1.gain(0, 1 - globalGain);
      }
      if (globalFreq != checkIR()){
        globalFreq = checkIR();
        waveform1.frequency(globalFreq);
      }
      break;
    case LOW_BAT_STATE:
      break;
  }

}

