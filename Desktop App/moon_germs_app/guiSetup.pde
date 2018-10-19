void setupGui() {
  PFont pfont = createFont("Arial", 10, true); //Create a font

  ControlFont font = new ControlFont(pfont, 10); //font, font-size

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR A

  oscAGroup = cp5.addGroup("Oscillator A")
    .setPosition(20, 100)
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
    .setGroup(oscAGroup)
    ;

  oscAVolumeKnob = cp5.addKnob("oscAVolume")
    .setRange(0, 1)
    .setValue(.5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscAGroup)
    ;


  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR B
  oscBGroup = cp5.addGroup("Oscillator B")
    .setPosition(20, 225)
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
    .setGroup(oscBGroup)
    ;

  oscBVolumeKnob = cp5.addKnob("oscBVolume")
    .setRange(0, 1)
    .setValue(0.5)
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
  // GUI COMPONENTS FOR LFO
  lfoGroup = cp5.addGroup("LFO")
    .setPosition(20, 350)
    .disableCollapse();

  lfoOnOffButton = cp5.addButton("lfoOnOff")
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
    .setRange(0, 10)
    .setValue(0)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Rate")
    .setGroup(lfoGroup)
    ;

  lfoAmountKnob = cp5.addKnob("lfoAmount")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(300, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    .setGroup(lfoGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR FILTER

  filterGroup = cp5.addGroup("Filter")
    .setPosition(20, 475)
    .disableCollapse();

  filterOnOffButton = cp5.addButton("filterOnOff")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(80, 80)
    .setGroup(filterGroup)
    ;

  filterCutoffKnob = cp5.addKnob("filterCutoff")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Cutoff")
    .setGroup(filterGroup)
    ;

  filterQKnob = cp5.addKnob("filterQ")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Resonance")
    .setGroup(filterGroup)
    ;

  filterAttackKnob = cp5.addKnob("filterAttack")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(300, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Attack")
    .setGroup(filterGroup)
    ;

  filterReleaseKnob = cp5.addKnob("filterRelease")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(400, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Release")
    .setGroup(filterGroup)
    ;

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR AMP ENVELOPE

  envelopeGroup = cp5.addGroup("Envelope")
    .setPosition(20, 600)
    .disableCollapse();

  ampAttackKnob = cp5.addKnob("ampAttack")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(0, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Attack")
    .setGroup(envelopeGroup)
    ;

  ampReleaseKnob = cp5.addKnob("ampRelease")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Release")
    .setGroup(envelopeGroup)
    ;

  masterVolumeKnob = cp5.addKnob("masterVolume")
    .setRange(0, 1)
    .setValue(0.5)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Master Volume")
    .setGroup(envelopeGroup)
    ;

  // GUI Components for Play Button
  playGroup = cp5.addGroup("Play")
    .setPosition(500, height-100)
    .disableCollapse()
    .hideBar()
    ;

  playButton = cp5.addButton("pressPlay")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(300, 80)
    .setGroup(playGroup)
    ;


  // GUI Components for COM PORT
  connectionGroup = cp5.addGroup("Connection")
    .setPosition(20, 30)
    .disableCollapse()
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
