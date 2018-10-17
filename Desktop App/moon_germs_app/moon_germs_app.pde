// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
Group connectionGroup;
ScrollableList comPortList;

Group oscAGroup;
Knob oscAWaveformKnob;
Knob oscAVolumeKnob;

Group oscBGroup;
Knob oscBWaveformKnob;
Knob oscBVolumeKnob;
Knob oscBDetuneKnob;

Group lfoGroup;
Knob lfoDestKnob;
Knob lfoRateKnob;
Knob lfoAmountKnob;
Button lfoOnOffButton;

Group filterGroup;
Knob filterQKnob;
Knob filterCutoffKnob;
Button filterOnOffButton;

Serial mgPort;
PFont alienEncounters;

String portName;
String incomingData;
boolean isDeviceConnected = false;

// Colors
color darkYellow = color(232, 173, 35);
color lightYellow = color(255, 200, 50);
color black = color(0);

// DEVICE VARIABLES
int play;
int oscAVolume;
int oscAWaveform;
int oscBVolume;
int oscBWaveform;
int oscBDetune;
int lfoRate;
int lfoAmount;
int lfoDest;
int lfoOnOff;
int filterQ;
int filterCutoff;
int filterOnOff;
int reverbOnOff;
int delayOnOff;
int triggerDest;
int attack;
int decay;

int[] deviceParameters = {
  play, 
  oscAVolume, 
  oscAWaveform, // 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
  oscBVolume, 
  oscBWaveform, 
  oscBDetune, 
  lfoRate, 
  lfoAmount, 
  lfoDest, 
  filterQ, 
  filterCutoff, 
  filterOnOff, 
  reverbOnOff, 
  delayOnOff, 
  triggerDest, 
  attack, 
  decay
};

void settings() {
  size(1000, 750);
}

void setup() {
  background(0);
  cp5 = new ControlP5(this); 
  alienEncounters = loadFont("SFAlienEncounters-48.vlw"); //Create a font
  setupGui();
  println(deviceParameters);
}

void draw() {
  background(0);
  textFont(alienEncounters, 48);
  fill(darkYellow);
  textAlign(RIGHT, TOP);
  text("moon germs", width-20, 20);
  if (comPortList.isMouseOver()) {
    comPortList.clear();
    for (int i = 0; i < Serial.list().length; i++) {
      comPortList.addItem(Serial.list()[i], i);
    }
  }

  if (isDeviceConnected) {
    println(mgPort.readString());
  }
}

void controlEvent(ControlEvent e) { //when something in the list is selected
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
