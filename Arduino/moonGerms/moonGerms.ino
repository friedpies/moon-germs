// Moon Germs Handheld Synthesizer
// Rev A Arduino Code, Octoboer 2018
// By Kenneth Marut (www.kennethmarut.com)
//
// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs


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

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button4 = Bounce(BUTTON_1, 15);
Bounce button3 = Bounce(BUTTON_2, 15);
Bounce button2 = Bounce(BUTTON_3, 15);
Bounce button1 = Bounce(BUTTON_4, 15);

int waveformType = WAVEFORM_SINE; // default waveform on both oscillators
uint8_t currentAnimation[18][8];// =  sineWaveBMP; // 20 frame array to hold animations
int animationLength = sizeof(sineWaveBMP) / sizeof(sineWaveBMP[0]); // computes number of frames of selected animation
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



void setup() {
  delay(2000); // Safety
  updateCurrentAnimation(sineWaveBMP, animationLength);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  matrix.begin(0x70); // Initialize display
  matrix.setRotation(1);

  //Audio setup
  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  oscillatorA.begin(waveformType);
  oscillatorA.amplitude(0.75);
  oscillatorA.frequency(centerFreq);
  oscillatorA.pulseWidth(0.5);

  oscillatorB.begin(waveformType);
  oscillatorB.amplitude(0.75);
  oscillatorB.frequency(centerFreq);
  oscillatorB.pulseWidth(0.15);

  pinkNoise.amplitude(1.0);

  mixer.gain(0, 1.0); // Osc A
  mixer.gain(1, 1.0); // Osc B
  mixer.gain(2, 0.1); // pink Noise


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

  // See "inputChecks" tab for function details
  readButton1();   // Detect if Play button is pressed and play note
  readButton2();   // Detect waveform button for press and switch waveform type
  readButton3();  // Increase octave
  readButton4(); // Decrease Octave
  readIRSensor(); // Adjust pitch
  readTrigger(); // Adjust LP filter

if (playAnimation){
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



