// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import controlP5.*;
import processing.serial.*;

PImage splashScreen;

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


void settings() {
  size(1000, 750);
}

void setup() {
  splashScreen = loadImage("moon-germs-splash.png");
  image(splashScreen, 0, 0);
  cp5 = new ControlP5(this); 
  alienEncounters = loadFont("SFAlienEncounters-48.vlw"); //Create a font
  setupGui();
}

void draw() {
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
}

// Event listener for all controller events
void controlEvent(ControlEvent e) { 
  if (isDeviceConnected) {
    mgPort.write(e.getName() + "," + e.getValue() + "\n");
  }

  if (e.isFrom(comPortList)) { // if dropdown list has been clicked
    if (isDeviceConnected) { // clear and stop existing serial port if device is connected
      mgPort.clear();
      mgPort.stop();
    }
    isDeviceConnected = true;
    portName = Serial.list()[int(e.getValue())]; // Connect to device
    mgPort = new Serial(this, portName, 115200);
    mgPort.write("CONNECT\n");
    println("Connected to " + mgPort);
  }
}

void keyPressed() {
  if (isDeviceConnected && keyBounce) {
    switch (key) {
    case 'z':
      mgPort.write("pressPlay,c1\n");
      break;
    case 'x':
      mgPort.write("pressPlay,d1\n");
      break;
    case 'c':
      mgPort.write("pressPlay,e1\n");
      break;
    case 'v':
      mgPort.write("pressPlay,f1\n");
      break;
    case 'b':
      mgPort.write("pressPlay,g1\n");
      break;
    case 'n':
      mgPort.write("pressPlay,a1\n");
      break;
    case 'm':
      mgPort.write("pressPlay,b1\n");
      break;
    case ',':
      mgPort.write("pressPlay,c2\n");
      break;
    case ' ':
      mgPort.write("pressPlay,1\n");
    }
    keyBounce = false;
  }
}

void keyReleased() {
  if (key == ' ' && isDeviceConnected) {
    mgPort.write("pressPlay,0\n"); 
    keyBounce = true;
  }
}
