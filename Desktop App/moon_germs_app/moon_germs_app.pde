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
Knob filterDecayKnob;

Group envelopeGroup;
Knob ampAttackKnob;
Knob ampDecayKnob;
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
float oscAVolume;
int oscAWaveform;
float oscBVolume;
int oscBWaveform;
int oscBDetune;
int lfoRate;
int lfoAmount;
int lfoDest;
int lfoOnOff;
int filterQ;
int filterAttack;
int filterDecay;
int filterCutoff;
int filterOnOff;
int reverbOnOff;
int delayOnOff;
int triggerDest;
int ampAttack;
int ampDecay;
int masterVolume;

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
    splashSequence(0.5, 1.0, 1.0);
    if (frameCount > (60 * 3)) {
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
