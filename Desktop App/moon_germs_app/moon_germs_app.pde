// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import controlP5.*;
import processing.serial.*;

PImage splashScreen;
boolean runOnce = true;

ControlP5 cp5;
Group connectionGroup;
ScrollableList comPortList;

Group oscAGroup;
RadioButton oscAWaveformCheckbox;
Knob oscAVolumeKnob;

Group oscBGroup;
RadioButton oscBWaveformCheckbox;
Knob oscBVolumeKnob;
Knob oscBDetuneKnob;

Group lfoGroup;
Knob lfoRateKnob;
Knob lfoAmountKnob;
Button lfoOnOffButton;
RadioButton lfoDestCheckbox;

Group filterGroup;
Button filterOnOffButton;
Knob filterCutoffKnob;
Knob filterQKnob;
Knob filterAttackKnob;
Knob filterReleaseKnob;

Group envelopeGroup;
Knob ampAttackKnob;
Knob ampReleaseKnob;
Knob masterVolumeKnob;

Group playGroup;
Button playButton;

Group loadSaveGroup;

Serial mgPort;
PFont alienEncounters;

String portName;
String incomingData;
boolean isDeviceConnected = false;

// Colors
color darkYellow = color(232, 173, 35);
color lightYellow = color(255, 200, 50);
color black = color(0);

boolean keyBounce = true;

// DEVICE VARIABLES
int bank;
int pressPlay;

float masterVolume;

float oscAVolume;
int oscAWaveform;

float oscBVolume;
int oscBWaveform;
int oscBDetune;

float noiseVolume;

boolean lfoOnOff;
int lfoRate;
int lfoAmount;
int lfoDest;

boolean filterOnOff;
float filterQ;
int filterCutoff;
int filterAttack;
int filterRelease;

int triggerDest;
int ampAttack;
int ampRelease;

String appState = "SPLASH";

void settings() {
  size(1000, 750);
}

void setup() {
  noStroke();
  splashScreen = loadImage("moon-germs-splash.png");
  frameRate(60); // 60 fps
  cp5 = new ControlP5(this); 
  alienEncounters = loadFont("SFAlienEncounters-48.vlw"); // Setup Font
}

void draw() {
  switch (appState) {
  case "SPLASH": // splash screen on start up
    splashSequence(0.5, 1, 1.5); // need to fix bug, not quite right
    if (frameCount > (60 * 2)) {
      appState = "NORMAL"; // switch states and setup GUI before moving to normal operation
      setupGui();
    }
    break;

  case "NORMAL":
    background(0);
    textFont(alienEncounters, 48);
    fill(darkYellow);
    textAlign(RIGHT, TOP);
    text("moon germs", width-20, 20);

    if (isDeviceConnected) {
      if (mgPort.available() > 0) {
        println(mgPort.readString());
      }
    }
    if (comPortList.isMousePressed()) {
      comPortList.clear();
      for (int i = 0; i < Serial.list().length; i++) {
        comPortList.addItem(Serial.list()[i], i);
      }
    }
    break;
  }
}
