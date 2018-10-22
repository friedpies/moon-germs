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
int darkYellow = color(230, 169, 64);
int lightYellow = color(255, 200, 50);
int black = color(0);

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

public void settings() {
  size(1000, 750);
}

public void setup() {
  noStroke();
  
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

public void draw() {

  switch (appState) {
  case "SPLASH": // splash screen on start up
    splashSequence(0.5f, 1, 1.5f); // need to fix bug, not quite right
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

public void showButtons(boolean[] buttonDisplays) {
  for (int i = 0; i < buttonDisplays.length; i++) {
    if (buttonDisplays[i] == true) {
      image(buttonOnImages[i], buttonCoordinates[i][0], buttonCoordinates[i][1]);
    } else {
      image(buttonOffImages[i], buttonCoordinates[i][0], buttonCoordinates[i][1]);
    }
  }
}
public void serialEvent(Serial mgPort) {
  incomingData = mgPort.readString();
  println("SERIAL EVENT: " + incomingData);

  String dataType = incomingData.substring(0, 4); // Check if incoming data contains information from Buttons Presses, Bank changes, Trigger Info, and Display Info, LOAD data etc.
  int bank;
  switch (dataType) {
  case "CONN":
    println("CONNECTED");
    connectionToggle.setValue(1.0f);
    isDeviceConnected = true;
    incomingData = "";
    mgPort.write("L~"); // auto Load data
    break;
  case "LOAD":
    bank = PApplet.parseInt(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    bankIndex = bank;
    parseData(incomingData);
    incomingData = "";
    break;
  case "BUTT":
    String buttonSubstring = incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1);
    int button = buttonSubstring.charAt(0) - '0';
    boolean value = PApplet.parseBoolean(buttonSubstring.charAt(1) - '0');
    buttonDisplays[button] = value;
    incomingData = "";
    break;

  case "BANK":
    bank = PApplet.parseInt(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    bankIndex = bank;
    updateGui(
      MasterVolume[bankIndex], 
      OscAWaveform[bankIndex], 
      OscAVolume[bankIndex], 
      OscBWaveform[bankIndex], 
      OscBVolume[bankIndex], 
      OscBDetune[bankIndex], 
      NoiseVolume[bankIndex], 
      LFOOnOff[bankIndex], 
      LFORate[bankIndex], 
      LFOAmount[bankIndex], 
      LFODest[bankIndex], 
      FilterOnOff[bankIndex], 
      FilterQ[bankIndex], 
      FilterCutoff[bankIndex], 
      TriggerDest[bankIndex][0], 
      TriggerDest[bankIndex][1], 
      TriggerDest[bankIndex][2], 
      TriggerDest[bankIndex][3], 
      AmpAttack[bankIndex], 
      AmpRelease[bankIndex]
      );
    //bankNumberbox.setValue(bank);
    incomingData = "";
    break;

  case "TRIG":
    int triggerValue = PApplet.parseInt(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    triggerDelta = PApplet.parseInt(map(triggerValue, 1019, 524, 0, 30));
    break;
  }
}

// Event listener for all controller events
public void controlEvent(ControlEvent e) { 
  if (e.isFrom(comPortList)) { // if dropdown list has been clicked
    if (isDeviceConnected) { // clear and stop existing serial port if device is connected
      mgPort.clear();
      mgPort.stop();
    }
    portName = Serial.list()[PApplet.parseInt(e.getValue())]; // Connect to device
    mgPort = new Serial(this, portName, 115200);
    mgPort.bufferUntil('~');
    mgPort.write("C~");
  } else if (e.isFrom(connectionToggle)) {
    if (e.getValue() == 0.0f) {
      mgPort.write("D~");
      mgPort.clear();
      mgPort.stop();
      isDeviceConnected = false;
      //println(e.getValue());
    }
  } else if (e.isFrom(closeButton)) {
    if (isDeviceConnected) {
      mgPort.write("D~");
    }
    exit();
  } else if (e.isFrom(loadButton)) {
    if (isDeviceConnected) {
      mgPort.write("L~");
    }
  } else {
    if (isDeviceConnected) {
      String value = "";
      if (e.isFrom(triggerDestCheckBox)) { // if click is from checkbox, send array
        float[] checkBoxArray = e.getArrayValue();
        for (int i = 0; i < checkBoxArray.length; i++) {
          value = value + str(PApplet.parseInt(checkBoxArray[i])); // send string of 4 bits representing each check box
        }
      } else if (isDeviceConnected) {
        value = str(e.getValue());
      }
      mgPort.write('P' + e.getName() + "," + value + "~"); // P for parameter
      //println(e.getName() + "," + value + "~");
    }
  }
}

public void stop() {
  if (isDeviceConnected) {
    mgPort.write("DISCONNECT~");
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
  }
}

// Function to Parse data dump from device
public void parseData(String loadData) {
  String[] dataPerBank = new String[numberOfBanks];

  for (int i = 0; i < numberOfBanks; i++) { // parse all incoming data into per-bank sections
    dataPerBank[i] = loadData.substring(loadData.indexOf("bank:" + str(i)), loadData.indexOf("bank:" + str(i + 1)));

    String[] splitData = split(dataPerBank[i], '\n'); // split up strings into individual variables

    // populate arrays with data, this needs to be refactored at some point
    MasterVolume[i] = PApplet.parseFloat(splitData[1].substring((splitData[1].indexOf(':') + 1), splitData[1].length()));

    OscAWaveform[i] = PApplet.parseInt(splitData[2].substring((splitData[2].indexOf(':') + 1), splitData[2].length()));
    OscAVolume[i] = PApplet.parseFloat(splitData[3].substring((splitData[3].indexOf(':') + 1), splitData[3].length()));

    OscBWaveform[i] = PApplet.parseInt(splitData[4].substring((splitData[4].indexOf(':') + 1), splitData[4].length()));
    OscBVolume[i] = PApplet.parseFloat(splitData[5].substring((splitData[5].indexOf(':') + 1), splitData[5].length()));
    OscBDetune[i] = PApplet.parseFloat(splitData[6].substring((splitData[6].indexOf(':') + 1), splitData[6].length()));

    NoiseVolume[i] = PApplet.parseFloat(splitData[7].substring((splitData[7].indexOf(':') + 1), splitData[7].length()));

    LFOOnOff[i] = PApplet.parseInt(splitData[8].substring((splitData[8].indexOf(':') + 1), splitData[8].length()));
    LFORate[i] = PApplet.parseFloat(splitData[9].substring((splitData[9].indexOf(':') + 1), splitData[9].length()));
    LFOAmount[i] = PApplet.parseFloat(splitData[10].substring((splitData[10].indexOf(':') + 1), splitData[10].length()));
    LFODest[i] = PApplet.parseInt(splitData[11].substring((splitData[11].indexOf(':') + 1), splitData[11].length()));

    FilterOnOff[i] = PApplet.parseInt(splitData[12].substring((splitData[12].indexOf(':') + 1), splitData[12].length()));
    FilterQ[i] = PApplet.parseFloat(splitData[13].substring((splitData[13].indexOf(':') + 1), splitData[13].length()));
    FilterCutoff[i] = PApplet.parseFloat(splitData[14].substring((splitData[14].indexOf(':') + 1), splitData[14].length()));

    TriggerDest[i][0] = PApplet.parseInt(splitData[15].substring((splitData[15].indexOf(':') + 1), splitData[15].length()));
    TriggerDest[i][1] = PApplet.parseInt(splitData[16].substring((splitData[16].indexOf(':') + 1), splitData[16].length()));
    TriggerDest[i][2] = PApplet.parseInt(splitData[17].substring((splitData[17].indexOf(':') + 1), splitData[17].length()));    
    TriggerDest[i][3] = PApplet.parseInt(splitData[18].substring((splitData[18].indexOf(':') + 1), splitData[18].length()));

    AmpAttack[i] = PApplet.parseInt(splitData[19].substring((splitData[19].indexOf(':') + 1), splitData[19].length()));
    AmpRelease[i] = PApplet.parseInt(splitData[20].substring((splitData[20].indexOf(':') + 1), splitData[20].length()));
  }
  //println(LFOOnOff);
}
public void setupGui() {

  PFont smallFont;
  smallFont = loadFont("Avenir-Light-10.vlw"); // Setup Font

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR A

  closeButton = cp5.addButton("closeButton")
    .setImages(loadImage("close-button-off.png"), loadImage("close-button-off.png"), loadImage("close-button-on.png"))
    .setPosition(966, 3)
    ;



  oscAWaveformRadioButton = cp5.addRadioButton("oscAWaveform")
    .setPosition(33, 250)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(6)
    .addItem("SINE A", 0) // 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
    .addItem("SAW A", 1)
    .addItem("REV SAW A", 6)
    .addItem("SQUARE A", 2)
    .addItem("TRIANGLE A", 3)
    .setArrayValue(defaultOscAWaveform)
    ;

  oscAVolumeKnob = cp5.addKnob("oscAVolume")
    .setPosition(132, 258)
    .setRange(0, 1.0f)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.5f)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    ;


  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR B

  oscBWaveformRadioButton = cp5.addRadioButton("oscBWaveform")
    .setPosition(33, 440)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(5)
    .addItem("SINE B", 0) // 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
    .addItem("SAW B", 1)
    .addItem("REV SAW B", 6)
    .addItem("SQUARE B", 2)
    .addItem("TRIANGLE B", 3)
    .setArrayValue(defaultOscBWaveform)
    ;

  oscBVolumeKnob = cp5.addKnob("oscBVolume")
    .setPosition(132, 443)
    .setRange(0, 1.0f)
    .setValue(0.5f)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    ;

  oscBDetuneKnob = cp5.addKnob("oscBDetune")
    .setPosition(232, 443)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setRange(0, 2)
    .setValue(1)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Detune")
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR FILTER

  filterOnOffToggle = cp5.addToggle("filterOnOff")
    .setPosition(37, 651)
    .setImages(loadImage("toggle-off.png"), loadImage("toggle-on.png"))
    .setValue(0)
    .setSize(80, 80)
    ;

  filterCutoffKnob = cp5.addKnob("filterCutoff")
    .setPosition(132, 621)
    .setRange(0, 8000)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(5)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Cutoff")
    ;

  filterQKnob = cp5.addKnob("filterQ")
    .setPosition(232, 621)
    .setRange(0.7f, 5)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setValue(0.707f)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Resonance")
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LFO

  lfoOnOffToggle = cp5.addToggle("lfoOnOff")
    .setPosition(367, 651)
    .setImages(loadImage("toggle-off.png"), loadImage("toggle-on.png"))
    .setValue(0)
    .setSize(40, 40)
    ;

  lfoRateKnob = cp5.addKnob("lfoRate")
    .setPosition(458, 621)
    .setRange(0, 10)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setValue(0)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Rate")
    ;

  lfoAmountKnob = cp5.addKnob("lfoAmount")
    .setPosition(564, 621)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setRange(0, 1.0f)
    .setValue(0.5f)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    ;



  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR AMP ENVELOPE

  ampAttackKnob = cp5.addKnob("ampAttack")
    .setPosition(697, 621)
    .setRange(0, 1000)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setValue(0)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Attack")
    ;

  ampReleaseKnob = cp5.addKnob("ampRelease")
    .setPosition(795, 621)
    .setRange(0, 1000)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Release")
    ;

  masterVolumeKnob = cp5.addKnob("masterVolume")
    .setPosition(895, 621)
    .setRange(0, 1)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.5f)
    .setLabelVisible(false)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Master Volume")
    ;


  ///////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR TRIGGER


  triggerDestCheckBox = cp5.addCheckBox("triggerDest")
    .setPosition(363, 465)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(6)
    .addItem("OSC B DETUNE", 0) // multiple destinations can be selected at once
    .addItem("FILTER", 1)
    .addItem("LFO RATE", 2)
    .addItem("LFO AMOUNT", 3)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LOAD SAVE

  //saveButton = cp5.addButton("saveButton")
  //  .setPosition(859, 52)
  //  .setSize(80, 60)
  //  .setImages(loadImage("save-button-off.png"), loadImage("save-button-on.png"), loadImage("save-button-off.png"))
  //  .setLabel("SAVE CHANGES")
  //  .setLabelVisible(false)
  //  ;

  //loadButton = cp5.addButton("loadButton")
  //  .setPosition(723, 52)
  //  .setSize(80, 60)
  //  .setImages(loadImage("load-button-off.png"), loadImage("load-button-on.png"), loadImage("load-button-off.png"))
  //  .setLabel("SAVE CHANGES")
  //  .setLabelVisible(false)
  //  ;

  // Graphical Components for Device
  displayCheckBox = cp5.addCheckBox("displayCheckBox")
    .setPosition(446, 245)
    .setSize(13, 13)
    .setItemsPerRow(8)
    .setSpacingColumn(3)
    .setSpacingRow(3)
    .setColorBackground(color(125, 125, 125))
    .setColorActive(color(255, 0, 0))
    .setColorForeground(color(255, 127, 127))
    ;
  for (int i = 0; i < 64; i++) {
    displayCheckBox.addItem(str(i), i);
  }
  displayCheckBox.hideLabels();


  // GUI Components for COM PORT

  comPortList = cp5.addScrollableList("comPortList")
    .setPosition(16, 69)
    .setItemHeight(20)
    .setFont(smallFont)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    .setBarHeight(25)
    .setHeight(17)
    .setSize(225, 200)
    .setLabel("SELECT COM PORT")
    .setColorBackground(darkYellow)
    .setColorForeground(lightYellow)
    .setColorLabel(black)
    .setColorValue(black)
    ;

  connectionToggle = cp5.addToggle("connectionToggle")
    .setPosition(257, 127)
    .setSize(50, 50)
    .setImages(loadImage("connection-toggle-off.png"), loadImage("connection-toggle-hover.png"), loadImage("connection-toggle-on.png"))
    .setValue(0)
    ;
}
// updates values of buttons/knobs/sliders when bank is switched
public void updateGui(
  float masterVolume, 
  int oscAWaveform, 
  float oscAVolume, 
  int oscBWaveform, 
  float oscBVolume, 
  float oscBDetune, 
  float noiseVolume, 
  int lfoOnOff, 
  float lfoRate, 
  float lfoAmount, 
  int lfoDest, 
  int filterOnOff, 
  float filterQ, 
  float filterCutoff, 
  int triggerDest0, 
  int triggerDest1, 
  int triggerDest2, 
  int triggerDest3, 
  int ampAttack, 
  int ampRelease
  ) {

  masterVolumeKnob.setValue(masterVolume);

  float[] waveformSetArray = new float[5];
  //0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
  switch(oscAWaveform) { // switch statement to map waveform values to an initialization array
  case  0:
    waveformSetArray[0] = 1;
    break;
  case 1:
    waveformSetArray[1] = 1;
    break;
  case 2:
    waveformSetArray[2] = 1;
    break;
  case 3:
    waveformSetArray[3] = 1;
    break; 
  case 6:
    waveformSetArray[4] = 1;
    break;
  }
  oscAWaveformRadioButton.setArrayValue(waveformSetArray);
  oscAVolumeKnob.setValue(oscAVolume);
  waveformSetArray = new float[5];
  switch(oscAWaveform) {
  case  0:
    waveformSetArray[0] = 1;
    break;
  case 1:
    waveformSetArray[1] = 1;
    break;
  case 2:
    waveformSetArray[2] = 1;
    break;
  case 3:
    waveformSetArray[3] = 1;
    break; 
  case 6:
    waveformSetArray[4] = 1;
    break;
  }
  oscBWaveformRadioButton.setArrayValue(waveformSetArray);
  oscBVolumeKnob.setValue(oscBVolume);
  oscBDetuneKnob.setValue(oscBDetune);
  //noiseVolumeKnob
  lfoOnOffToggle.setValue(lfoOnOff);
  lfoRateKnob.setValue(lfoRate);
  lfoAmountKnob.setValue(lfoAmount);
  //lfoDestRadioButton.setValue(lfoDest);
  filterOnOffToggle.setValue(filterOnOff);
  filterQKnob.setValue(filterQ);
  filterCutoffKnob.setValue(filterCutoff);
  float[] triggerDestArray = {triggerDest0, triggerDest1, triggerDest2, triggerDest3};
  triggerDestCheckBox.setArrayValue(triggerDestArray);
  ampAttackKnob.setValue(ampAttack);
  ampReleaseKnob.setValue(ampRelease);
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "moon_germs_app" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
