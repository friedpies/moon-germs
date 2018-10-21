void setupGui() {

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
    .setRange(0, 1.0)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.5)
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
    .setRange(0, 1.0)
    .setValue(0.5)
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
    .setRange(0, 20000)
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
    .setRange(0.7, 5)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setLabelVisible(false)
    .setValue(0.707)
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
    .setRange(0, 20)
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
    .setRange(0, 1.0)
    .setValue(0.5)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    ;



  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR AMP ENVELOPE

  ampAttackKnob = cp5.addKnob("ampAttack")
    .setPosition(697, 621)
    .setRange(0, 11880)
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
    .setRange(0, 11880)
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
    .setValue(0.5)
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

  saveButton = cp5.addButton("saveButton")
    .setPosition(859, 52)
    .setSize(80, 60)
    .setImages(loadImage("save-button-off.png"), loadImage("save-button-on.png"), loadImage("save-button-off.png"))
    .setLabel("SAVE CHANGES")
    .setLabelVisible(false)
    ;

  loadButton = cp5.addButton("loadButton")
    .setPosition(723, 52)
    .setSize(80, 60)
    .setImages(loadImage("load-button-off.png"), loadImage("load-button-on.png"), loadImage("load-button-off.png"))
    .setLabel("SAVE CHANGES")
    .setLabelVisible(false)
    ;

  bankNumberbox = cp5.addNumberbox("bankNumberbox")
    .setPosition(380, 55)
    .setSize(100, 50)
    .setLabelVisible(false)
    .setColorBackground(darkYellow)
    .setColorForeground(lightYellow)
    .setColorLabel(black)
    .setColorValue(black)
    .setScrollSensitivity(1)
    .setValue(1)
    .setRange(0, 3)
    ;

  bankDecButton = cp5.addButton("bankDecButton")
    .setPosition(349, 61)
    .setSize(18, 36)
    .setImages(loadImage("bank-dec-off.png"), loadImage("bank-dec-on.png"), loadImage("bank-dec-off.png"))
    .setLabel("Dec Bank")
    .setLabelVisible(false)
    ;

  bankIncButton = cp5.addButton("bankIncButton")
    .setPosition(492, 61)
    .setSize(18, 36)
    .setImages(loadImage("bank-inc-off.png"), loadImage("bank-inc-on.png"), loadImage("bank-inc-off.png"))
    .setLabel("Dec Bank")
    .setLabelVisible(false)
    ;

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
