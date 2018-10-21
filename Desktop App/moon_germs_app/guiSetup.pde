void setupGui() {
  PFont pfont = createFont("Arial", 10, true); //Create a font

  ControlFont font = new ControlFont(pfont, 10); //font, font-size

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR A

  closeButton = cp5.addButton("closeButton")
    .setImages(loadImage("close-button-off.png"), loadImage("close-button-off.png"), loadImage("close-button-on.png"))
    .setPosition(966, 3)
    ;

  oscAGroup = cp5.addGroup("Oscillator A")
    .setPosition(15, 240)
    .hideBar()
    .disableCollapse();

  oscAWaveformRadioButton = cp5.addRadioButton("oscAWaveform")
    .setPosition(20, 10)
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
    .setGroup(oscAGroup)
    ;

  oscAVolumeKnob = cp5.addKnob("oscAVolume")
    .setRange(0, 1.0)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscAGroup)
    ;


  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR B
  oscBGroup = cp5.addGroup("Oscillator B")
    .setPosition(15, 430)
    .hideBar()
    .disableCollapse();

  oscBWaveformRadioButton = cp5.addRadioButton("oscBWaveform")
    .setPosition(20, 10)
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
    .setGroup(oscBGroup)
    ;

  oscBVolumeKnob = cp5.addKnob("oscBVolume")
    .setRange(0, 1.0)
    .setValue(0.5)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscBGroup)
    ;

  oscBDetuneKnob = cp5.addKnob("oscBDetune")
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
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
    .setPosition(0, 30)
    .setImages(loadImage("toggle-off.png"), loadImage("toggle-on.png"))
    .setValue(0)
    .setSize(80, 80)
    .setGroup(filterGroup)
    ;

  filterCutoffKnob = cp5.addKnob("filterCutoff")
    .setRange(0, 20000)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Cutoff")
    .setGroup(filterGroup)
    ;

  filterQKnob = cp5.addKnob("filterQ")
    .setRange(0.7, 5)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.707)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Resonance")
    .setGroup(filterGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LFO
  lfoGroup = cp5.addGroup("LFO")
    .setPosition(370, 620)
    .hideBar()
    .disableCollapse();

  lfoOnOffToggle = cp5.addToggle("lfoOnOff")
    .setPosition(0, 30)
    .setImages(loadImage("toggle-off.png"), loadImage("toggle-on.png"))
    .setValue(0)
    .setSize(40, 40)
    .setGroup(lfoGroup)
    ;

  lfoDestRadioButton = cp5.addRadioButton("lfoDest")
    .setPosition(100, 10)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    //.setSize(15, 15)
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
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Rate")
    .setGroup(lfoGroup)
    ;

  lfoAmountKnob = cp5.addKnob("lfoAmount")
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setRange(0, 1.0)
    .setValue(0.5)
    .setPosition(300, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    .setGroup(lfoGroup)
    ;



  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR AMP ENVELOPE

  envelopeGroup = cp5.addGroup("Envelope")
    .setPosition(400, 40)
    .hideBar()
    .disableCollapse();

  ampAttackKnob = cp5.addKnob("ampAttack")
    .setRange(0, 11880)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0)
    .setPosition(0, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Attack")
    .setGroup(envelopeGroup)
    ;

  ampReleaseKnob = cp5.addKnob("ampRelease")
    .setRange(0, 11880)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Release")
    .setGroup(envelopeGroup)
    ;

  masterVolumeKnob = cp5.addKnob("masterVolume")
    .setRange(0, 1)
    .setColorBackground(darkYellow)
    .setColorForeground(0)
    .setColorActive(0)
    .setValue(0.5)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Master Volume")
    .setGroup(envelopeGroup)
    ;


  ///////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR TRIGGER

  triggerGroup = cp5.addGroup("triggerGroup")
    .setPosition(350, 450)
    .hideBar()
    .disableCollapse();

  triggerDestCheckBox = cp5.addCheckBox("triggerDest")
    .setPosition(20, 10)
    .setImages(loadImage("radio-button-off.png"), loadImage("radio-button-hover.png"), loadImage("radio-button-on.png"))
    .setSize(15, 15)
    .setItemsPerRow(1)
    .setSpacingColumn(20)
    .setSpacingRow(6)
    .addItem("OSC B DETUNE", 0) // multiple destinations can be selected at once
    .addItem("FILTER", 1)
    .addItem("LFO RATE", 2)
    .addItem("LFO AMOUNT", 3)
    .setGroup(triggerGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR LOAD SAVE
  loadSaveGroup = cp5.addGroup("loadSaveGroup")
    .setPosition(500, 60)
    .disableCollapse()
    .hideBar()
    ;

  bankNumberbox = cp5.addNumberbox("bankNumberbox")
    .setPosition(360, 216)
    .setSize(100, 50)
    .setColorBackground(darkYellow)
    .setColorForeground(lightYellow)
    .setColorLabel(black)
    .setColorValue(black)
    .setScrollSensitivity(1)
    .setValue(1)
    .setRange(0, 3)
    ;


  // GUI Components for COM PORT
  connectionGroup = cp5.addGroup("Connection")
    .setPosition(35, 50)
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
