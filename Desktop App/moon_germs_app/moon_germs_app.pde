// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import controlP5.*;
import processing.serial.*;

PImage splashScreen;
PImage appBackground;

boolean runOnce = true; // boolean to run splash screen once

ControlP5 cp5;
Button closeButton;

Group connectionGroup;
ScrollableList comPortList;

Group oscAGroup;
RadioButton oscAWaveformRadioButton;
Knob oscAVolumeKnob;

Group oscBGroup;
RadioButton oscBWaveformRadioButton;
Knob oscBVolumeKnob;
Knob oscBDetuneKnob;

Group lfoGroup;
Knob lfoRateKnob;
Knob lfoAmountKnob;
Toggle lfoOnOffToggle;
RadioButton lfoDestRadioButton;

Group filterGroup;
Toggle filterOnOffToggle;
Knob filterCutoffKnob;
Knob filterQKnob;

Group envelopeGroup;
Knob ampAttackKnob;
Knob ampReleaseKnob;
Knob masterVolumeKnob;

Group triggerGroup;
CheckBox triggerDestCheckBox;

Group loadSaveGroup;
Numberbox bankNumberbox;
Button loadButton;
Button saveButton;

Serial mgPort;
PFont alienEncounters;

String portName;
String incomingData;
boolean isDeviceConnected = false;

// Colors
color darkYellow = color(230, 169, 64);
color lightYellow = color(255, 200, 50);
color black = color(0);

boolean keyBounce = true;

//SYNCED VARIABLES WITH DEVICE
String loadData = ""; // String to hold all incoming data
int bankIndex = 0;
final int numberOfBanks = 4;

float[] MasterVolume = new float[numberOfBanks];

int[] OscAWaveform = new int[numberOfBanks];
float[] OscAVolume = new float[numberOfBanks];

int[] OscBWaveform = new int[numberOfBanks];
float[] OscBVolume = new float[numberOfBanks];
float[] OscBDetune = new float[numberOfBanks];

float[] NoiseVolume = new float[numberOfBanks];

int[] LFOOnOff = new int[numberOfBanks];
float[] LFORate = new float[numberOfBanks];
float[] LFOAmount = new float[numberOfBanks];
int[] LFODest = new int[numberOfBanks];

int[] FilterOnOff = new int[numberOfBanks];
float[] FilterQ = new float[numberOfBanks];
float[] FilterCutoff = new float[numberOfBanks];

int[][] TriggerDest = new int[numberOfBanks][4];

int[] AmpAttack = new int[numberOfBanks];
int[] AmpRelease = new int[numberOfBanks];


// DEVICE VARIABLES
//int bank;
//int playPause;

//float masterVolume;

//float oscAVolume;
//int oscAWaveform;
float[] defaultOscAWaveform = {0, 0, 1, 0, 0};

//float oscBVolume;
//int oscBWaveform;
float[] defaultOscBWaveform = {1, 0, 0, 0, 0};
//int oscBDetune;

//float noiseVolume;

//boolean lfoOnOff;
//int lfoRate;
//float lfoAmount;
//int lfoDest;

//boolean filterOnOff;
//float filterQ;
//float filterCutoff;

//int triggerDest;
//int ampAttack;
//int ampRelease;

String appState = "SPLASH";

void settings() {
  size(1000, 750);
}

void setup() {
  noStroke();
  smooth(2);
  splashScreen = loadImage("moon-germs-splash3d.png");

  frameRate(60); // 60 fps
  cp5 = new ControlP5(this); 
  alienEncounters = loadFont("SFAlienEncounters-48.vlw"); // Setup Font
}

void draw() {
  print(mouseX); print(" "); println(mouseY);
  switch (appState) {
  case "SPLASH": // splash screen on start up
    splashSequence(0.5, 1, 1.5); // need to fix bug, not quite right
    if (frameCount > (30 * 2)) {
      appState = "NORMAL"; // switch states and setup GUI before moving to normal operation
      setupGui();

      appBackground = loadImage("app-design.png");
    }
    break;

  case "NORMAL":
    image(appBackground, 0, 0);
    textFont(alienEncounters, 48);
    fill(darkYellow);


    if (comPortList.isMousePressed()) {
      comPortList.clear();
      for (int i = 0; i < Serial.list().length; i++) {
        comPortList.addItem(Serial.list()[i], i);
      }
    }
    break;

  case "LOADING": 
    if (isDeviceConnected) {
      while (mgPort.available() > 0) {
        loadData = mgPort.readStringUntil(';'); // loads all data from Device
      }
      parseData(loadData);
    } 
    appState = "NORMAL";
    //println(loadData);
    break;
  }
}
