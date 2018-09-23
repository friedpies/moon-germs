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

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button1 = Bounce(BUTTON_1, 15);
Bounce button2 = Bounce(BUTTON_2, 15);
Bounce button3 = Bounce(BUTTON_3, 15);
Bounce button4 = Bounce(BUTTON_4, 15);


int waveform_type = WAVEFORM_SINE;
int triggerRead;
int infraredRead;
float globalFreq;
float globalGain;
int filterFreq = 10000;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  matrix.begin(0x70); // Initialize display

  //Audio setup
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  oscillatorA.begin(WAVEFORM_SAWTOOTH);
  oscillatorA.amplitude(0.75);
  oscillatorA.frequency(82.41);
  oscillatorA.pulseWidth(0.15);

  oscillatorB.begin(WAVEFORM_SAWTOOTH);
  oscillatorB.amplitude(0.75);
  oscillatorB.frequency(123);
  oscillatorB.pulseWidth(0.15);

  pinkNoise.amplitude(1.0);

  mixer.gain(0, 1.0); // Osc A
  mixer.gain(1, 1.0); // Osc B
  mixer.gain(2, 0.3); // pink Noise

  lpFilter.frequency(filterFreq);
  lpFilter.resonance(2.0);
  
  envelope.attack(1000);
  envelope.decay(0);
  envelope.sustain(1.0);
  envelope.release(2000);
}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  checkButton1();
  checkButton2();
  checkTrigger();

  switch (deviceState) {

  }
}

