import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class moon_germs_app extends PApplet {

// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT




PImage splashScreen;
PImage appBackground;
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
Toggle lfoOnOffToggle;
RadioButton lfoDestCheckbox;

Group filterGroup;
Toggle filterOnOffToggle;
Knob filterCutoffKnob;
Knob filterQKnob;

Group envelopeGroup;
Knob ampAttackKnob;
Knob ampReleaseKnob;
Knob masterVolumeKnob;

Group playGroup;
Button playButton;

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
int darkYellow = color(233, 179, 75);
int lightYellow = color(255, 200, 50);
int black = color(0);

boolean keyBounce = true;

// DEVICE VARIABLES
int bank;
int playPause;

float masterVolume;

float oscAVolume;
int oscAWaveform;
float[] defaultOscAWaveform = {1, 0, 0, 0, 0};

float oscBVolume;
int oscBWaveform;
float[] defaultOscBWaveform = {1, 0, 0, 0, 0};
int oscBDetune;

float noiseVolume;

boolean lfoOnOff;
int lfoRate;
float lfoAmount;
int lfoDest;

boolean filterOnOff;
float filterQ;
float filterCutoff;

int triggerDest;
int ampAttack;
int ampRelease;

String appState = "SPLASH";

public void settings() {
  size(1000, 750);
}

public void setup() {
  noStroke();
  splashScreen = loadImage("moon-germs-splash3d.png");
  appBackground = loadImage("app-design.png");
  frameRate(60); // 60 fps
  cp5 = new ControlP5(this); 
  alienEncounters = loadFont("SFAlienEncounters-48.vlw"); // Setup Font
}

public void draw() {
  switch (appState) {
  case "SPLASH": // splash screen on start up
    splashSequence(0.5f, 1, 1.5f); // need to fix bug, not quite right
    if (frameCount > (30 * 2)) {
      appState = "NORMAL"; // switch states and setup GUI before moving to normal operation
      setupGui();
    }
    break;

  case "NORMAL":
    image(appBackground, 0, 0);
    textFont(alienEncounters, 48);
    fill(darkYellow);

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

// Function to "Pixelize" an image for aesthetic effect, wink to Teenage Engineering's website
public void pixelateImage(int pixelWidth, PImage image) {
  int ratio = width/height;
  int pixelHeight = pixelWidth * ratio;
  for (int x = 0; x < width; x += pixelWidth) {
    for (int y = 0; y < height; y += pixelHeight) {
      fill(image.get(x, y));
      rect(x, y, pixelWidth, pixelHeight);
    }
  }
}

public void splashSequence(float time1, float time2, float time3) {
  image(splashScreen, 0, 0); // show splash screen for X amount of time
  if (frameCount < (30 * time1)) {
    pixelateImage(15, splashScreen); // pixelates splashscreen image (for fun)
  } else if (frameCount < (30 * time2)) {
    pixelateImage(5, splashScreen);
  } else if (frameCount <= (30 * time3)) {
    pixelateImage(2, splashScreen);
  }
}

// Event listener for all controller events
public void controlEvent(ControlEvent e) { 
  if (isDeviceConnected) {
    mgPort.write(e.getName() + "," + e.getValue() + "\n");
  }

  if (e.isFrom(comPortList)) { // if dropdown list has been clicked
    if (isDeviceConnected) { // clear and stop existing serial port if device is connected
      mgPort.clear();
      mgPort.stop();
    }
    isDeviceConnected = true;
    portName = Serial.list()[PApplet.parseInt(e.getValue())]; // Connect to device
    mgPort = new Serial(this, portName, 115200);
    mgPort.write("CONNECT\n");
    println("Connected to " + mgPort);
  }
}

public void keyPressed() {
  if (isDeviceConnected && keyBounce) {
    switch (key) {
    case 'z':
      mgPort.write("playPause,c1\n");
      break;
    case 'x':
      mgPort.write("playPause,d1\n");
      break;
    case 'c':
      mgPort.write("playPause,e1\n");
      break;
    case 'v':
      mgPort.write("playPause,f1\n");
      break;
    case 'b':
      mgPort.write("playPause,g1\n");
      break;
    case 'n':
      mgPort.write("playPause,a1\n");
      break;
    case 'm':
      mgPort.write("playPause,b1\n");
      break;
    case ',':
      mgPort.write("playPause,c2\n");
      break;
    case ' ':
      mgPort.write("playPause,1\n");
    }
    keyBounce = false;
  }
}

public void keyReleased() {
  if (key == ' ' && isDeviceConnected) {
    mgPort.write("playPause,0\n"); 
    keyBounce = true;
  }
}
public void setupGui() {
  PFont pfont = createFont("Arial", 10, true); //Create a font

  ControlFont font = new ControlFont(pfont, 10); //font, font-size

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR A

  oscAGroup = cp5.addGroup("Oscillator A")
    .setPosition(37, 240)
    .hideBar()
    .disableCollapse();

  oscAWaveformCheckbox = cp5.addRadioButton("oscAWaveform")
    .setPosition(0, 10)
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(5)
    .addItem("SINE A", 0) // 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
    .addItem("SAW A", 1)
    .addItem("REV SAW A", 6)
    .addItem("SQUARE A", 2)
    .addItem("TRIANGLE A", 3)
    .setArrayValue(defaultOscAWaveform)
    .setGroup(oscAGroup)
    ;

  oscAVolumeKnob = cp5.addKnob("oscAVolume")
    .setRange(0, 1.0f)
    .setValue(0.5f)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscAGroup)
    ;


  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR B
  oscBGroup = cp5.addGroup("Oscillator B")
    .setPosition(37, 430)
    .hideBar()
    .disableCollapse();

  oscBWaveformCheckbox = cp5.addRadioButton("oscBWaveform")
    .setPosition(0, 10)
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(5)
    .addItem("SINE B", 0) // 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
    .addItem("SAW B", 1)
    .addItem("REV SAW B", 6)
    .addItem("SQUARE B", 2)
    .addItem("TRIANGLE B", 3)
    .setArrayValue(defaultOscBWaveform)
    .setGroup(oscBGroup)
    ;

  oscBVolumeKnob = cp5.addKnob("oscBVolume")
    .setRange(0, 1.0f)
    .setValue(0.5f)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscBGroup)
    ;

  oscBDetuneKnob = cp5.addKnob("oscBDetune")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Detune")
    .setGroup(oscBGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR FILTER

  filterGroup = cp5.addGroup("Filter")
    .setPosition(37, 620)
    .hideBar()
    .disableCollapse();

  filterOnOffToggle = cp5.addToggle("filterOnOff")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(80, 80)
    .setGroup(filterGroup)
    ;

  filterCutoffKnob = cp5.addKnob("filterCutoff")
    .setRange(0, 20000)
    .setValue(5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Cutoff")
    .setGroup(filterGroup)
    ;

  filterQKnob = cp5.addKnob("filterQ")
    .setRange(0.7f, 5)
    .setValue(0.707f)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Resonance")
    .setGroup(filterGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LFO
  lfoGroup = cp5.addGroup("LFO")
    .setPosition(400, 350)
    .hideBar()
    .disableCollapse();

  lfoOnOffToggle = cp5.addToggle("lfoOnOff")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(80, 80)
    .setGroup(lfoGroup)
    ;

  lfoDestCheckbox = cp5.addRadioButton("lfoDest")
    .setPosition(100, 10)
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(5)
    .addItem("OSC A", 0)
    .addItem("OSC B", 25)
    .addItem("OSC A + B", 50)
    .addItem("FILTER CUTOFF", 75)
    .setGroup(lfoGroup)
    ;

  lfoRateKnob = cp5.addKnob("lfoRate")
    .setRange(0, 20)
    .setValue(0)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Rate")
    .setGroup(lfoGroup)
    ;

  lfoAmountKnob = cp5.addKnob("lfoAmount")
    .setRange(0, 1.0f)
    .setValue(0.5f)
    .setPosition(300, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    .setGroup(lfoGroup)
    ;



  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR AMP ENVELOPE

  envelopeGroup = cp5.addGroup("Envelope")
    .setPosition(400, 600)
    .hideBar()
    .disableCollapse();

  ampAttackKnob = cp5.addKnob("ampAttack")
    .setRange(0, 11880)
    .setValue(0)
    .setPosition(0, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Attack")
    .setGroup(envelopeGroup)
    ;

  ampReleaseKnob = cp5.addKnob("ampRelease")
    .setRange(0, 11880)
    .setValue(0)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Release")
    .setGroup(envelopeGroup)
    ;

  masterVolumeKnob = cp5.addKnob("masterVolume")
    .setRange(0, 1)
    .setValue(0.5f)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Master Volume")
    .setGroup(envelopeGroup)
    ;

  ///////////////////////////////////////////////////
  // GUI Components for Play Button
  playGroup = cp5.addGroup("Play")
    .setPosition(500, 60)
    .disableCollapse()
    .hideBar()
    ;

  playButton = cp5.addButton("playPause")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(300, 80)
    .setGroup(playGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LOAD SAVE
  loadSaveGroup =   playGroup = cp5.addGroup("loadSaveGroup")
    .setPosition(500, 60)
    .disableCollapse()
    .hideBar()
    ;

  bankNumberbox = cp5.addNumberbox("bankNumberbox")
    .setPosition(0, 10)
    .setSize(100, 50)
    .setScrollSensitivity(1)
    .setValue(1)
    .setRange(1, 10)
    .setGroup(loadSaveGroup)
    ;


  // GUI Components for COM PORT
  connectionGroup = cp5.addGroup("Connection")
    .setPosition(20, 30)
    .disableCollapse()
    .hideBar()
    ;

  comPortList = cp5.addScrollableList("COM PORT")
    .setPosition(0, 10)
    .setItemHeight(20)
    .setFont(font)
    .setBarHeight(25)
    .setHeight(height/10)
    .setSize(200, 200)
    .setColorBackground(darkYellow)
    .setColorForeground(lightYellow)
    .setColorLabel(black)
    .setColorValue(black)
    .setGroup(connectionGroup);
}

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#050101", "--hide-stop", "moon_germs_app" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
