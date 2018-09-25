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
#include "states.h"
#include "bitMaps.h"
#include "noteLookup.h"
#include "aLookup.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button1 = Bounce(BUTTON_1, 15);
Bounce button2 = Bounce(BUTTON_2, 15);
Bounce button3 = Bounce(BUTTON_3, 15);
Bounce button4 = Bounce(BUTTON_4, 15);

int waveformType = WAVEFORM_SAWTOOTH;
int triggerRead;
const int numReadings = 300; //smoothing factor
int infraredReadings[numReadings];
int readIndex = 0;
float readingAverage;
float mappedAverage;
float globalFreq = noteA[4]; // set global frequency to A3
float octaveMultiplier = 1.0;
float bendFactor;
float globalGain;
int filterFreq = 20000;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  matrix.begin(0x70); // Initialize display

  //Audio setup
  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  oscillatorA.begin(WAVEFORM_PULSE);
  oscillatorA.amplitude(0.75);
  oscillatorA.frequency(globalFreq);
  oscillatorA.pulseWidth(0.5);

  oscillatorB.begin(WAVEFORM_SAWTOOTH);
  oscillatorB.amplitude(0.75);
  oscillatorB.frequency(globalFreq);
  oscillatorB.pulseWidth(0.15);

  pinkNoise.amplitude(1.0);

  mixer.gain(0, 1.0); // Osc A
  mixer.gain(1, 1.0); // Osc B
  mixer.gain(2, 0.0); // pink Noise

  lpFilter.frequency(filterFreq);
  lpFilter.resonance(.70);

  envelope.attack(100);
  envelope.decay(0);
  envelope.sustain(1.0);
  envelope.release(1000);

  amp.gain(6);

  bootupAnimation();

}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();


  // Detect if Play button is pressed and play note
  if (button1.fallingEdge()) {
    matrix.clear();
    matrix.writeDisplay();
    envelope.noteOn();
  } else if (button1.risingEdge()) {
    matrix.clear();
    matrix.writeDisplay();
    envelope.noteOff();
  }

  // Detect waveform button for press and switch waveform type
  if (button2.fallingEdge()) {
    switch (waveformType) {
      case WAVEFORM_SAWTOOTH:
        waveformType = WAVEFORM_SQUARE;
        break;

      case WAVEFORM_SQUARE:
        waveformType = WAVEFORM_TRIANGLE;
        break;

      case WAVEFORM_TRIANGLE:
        waveformType = WAVEFORM_SINE;
        break;

      case WAVEFORM_SINE:
        waveformType = WAVEFORM_SAWTOOTH;
        break;
    }
    AudioNoInterrupts();
    oscillatorA.begin(waveformType);
    oscillatorB.begin(waveformType);
    AudioInterrupts();
  }

  // Increase Octave if button 3 is pressed
  if (button3.fallingEdge()) {
    if (octaveMultiplier == 0.25){
      octaveMultiplier = 0.5;
    }
    else if (octaveMultiplier == 0.5) {
      octaveMultiplier = 1.0;
    }
    else if (octaveMultiplier == 1.0) {
      octaveMultiplier = 2.0;
    }
  }

  // Decrease Octave if button 4 is pressed
  if (button4.fallingEdge()) {
    if (octaveMultiplier == 0.5) {
      octaveMultiplier = 0.25;
    }
    else if (octaveMultiplier == 1.0) {
      octaveMultiplier = 0.5;
    }
    else if (octaveMultiplier == 2.0) {
      octaveMultiplier = 1.0;
    }
  }

  readIRSensor();

  
  //  infraredRead = mapIRtoFloat(analogRead(IR_SENSOR));
  //  bendFactor = pow(2, infraredRead);
  //  oscillatorA.frequency(globalFreq * 1.5);
  //  oscillatorB.frequency(globalFreq * bendFactor);

//  checkButton2();
  checkTrigger();

}

void readIRSensor(){
  infraredReadings[readIndex] = analogRead(IR_SENSOR);
  readIndex++;

  // Smoothing function for analog Read
  if (readIndex == numReadings) {
    for (int i = 0; i < numReadings; i++) {
      readingAverage = readingAverage + infraredReadings[i];
    }
    readingAverage = readingAverage / numReadings;
    mappedAverage = mapIRtoFloat(readingAverage);
    bendFactor = pow(2, mappedAverage);
    oscillatorA.frequency(globalFreq * bendFactor * octaveMultiplier * 1.011); // 1.01 added for slight detune
    oscillatorB.frequency(globalFreq * bendFactor * octaveMultiplier);
    readIndex = 0;
    readingAverage = 0;
  }
};

