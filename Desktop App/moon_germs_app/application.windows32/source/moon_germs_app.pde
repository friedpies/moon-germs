// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import controlP5.*;
import processing.serial.*;

PImage splashScreen;
PImage appBackground;
PImage[] buttonOnImages = new PImage[4];
PImage[] buttonOffImages = new PImage[4];
PImage triggerImage; 
PImage drawingOverlayImage;
PFont sevenSegment;
boolean runOnce = true; // boolean to run splash screen once

ControlP5 cp5;
Button closeButton;

ScrollableList comPortList;
Toggle connectionToggle;

RadioButton oscAWaveformRadioButton;
Knob oscAVolumeKnob;

RadioButton oscBWaveformRadioButton;
Knob oscBVolumeKnob;
Knob oscBDetuneKnob;

Knob lfoRateKnob;
Knob lfoAmountKnob;
Toggle lfoOnOffToggle;
RadioButton lfoDestRadioButton;

Toggle filterOnOffToggle;
Knob filterCutoffKnob;
Knob filterQKnob;

Knob ampAttackKnob;
Knob ampReleaseKnob;
Knob masterVolumeKnob;

CheckBox triggerDestCheckBox;

Button loadButton;
Button saveButton;

CheckBox displayCheckBox;


Serial mgPort;

String portName;
String incomingData = "";
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



float[] defaultOscAWaveform = {0, 0, 1, 0, 0};
float[] defaultOscBWaveform = {1, 0, 0, 0, 0};


boolean[] buttonDisplays = {false, false, false, false};

//PImage[] buttonOffImages = {loadImage("button1-off.png"), loadImage("button2-off.png"), loadImage("button3-off.png"), loadImage("button4-off.png")};
int[][] buttonCoordinates = {
  {579, 151}, 
  {679, 151}, 
  {757, 152}, 
  {828, 152}};

int triggerDelta;
String appState = "SPLASH";

void settings() {
  size(1000, 750);
}

void setup() {
  noStroke();
  smooth(2);
  splashScreen = loadImage("moon-germs-splash3d.png");
  buttonOnImages[0] = loadImage("button1-on.png");
  buttonOnImages[1] = loadImage("button2-on.png");  
  buttonOnImages[2] = loadImage("button3-on.png");  
  buttonOnImages[3] = loadImage("button4-on.png");

  buttonOffImages[0] = loadImage("button1-off.png");
  buttonOffImages[1] = loadImage("button2-off.png");  
  buttonOffImages[2] = loadImage("button3-off.png");  
  buttonOffImages[3] = loadImage("button4-off.png");
  triggerImage = loadImage("trigger.png");
  drawingOverlayImage = loadImage("drawing-overlay.png");
  sevenSegment = loadFont("SevenSegmentRegular-53.vlw");
  textFont(sevenSegment);
  textAlign(CENTER, CENTER);
  frameRate(60); // 60 fps
  cp5 = new ControlP5(this);
}

void draw() {

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
    image(triggerImage, 532 + triggerDelta, 419);
    image(drawingOverlayImage, 0, 0);
    fill(255, 0, 0);
    text(bankIndex, 430, 80);
    showButtons(buttonDisplays);
    fill(darkYellow);

    //if (incomingData.equals("CONNECTED~")) {
    //  incomingData = "";
    //  println("CONNECTED");
    //  connectionToggle.setValue(1.0);
    //  isDeviceConnected = true;
    //}

    if (comPortList.isMousePressed()) {
      comPortList.clear();
      for (int i = 0; i < Serial.list().length; i++) {
        comPortList.addItem(Serial.list()[i], i);
      }
    }
    break;
  }
}

void showButtons(boolean[] buttonDisplays) {
  for (int i = 0; i < buttonDisplays.length; i++) {
    if (buttonDisplays[i] == true) {
      image(buttonOnImages[i], buttonCoordinates[i][0], buttonCoordinates[i][1]);
    } else {
      image(buttonOffImages[i], buttonCoordinates[i][0], buttonCoordinates[i][1]);
    }
  }
}
