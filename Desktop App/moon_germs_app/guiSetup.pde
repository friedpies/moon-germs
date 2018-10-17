void setupGui() {
  PFont pfont = createFont("Arial", 10, true); //Create a font

  ControlFont font = new ControlFont(pfont, 10); //font, font-size

  //////////////////////////////////////////////////////////////
  // GUI COMPONENTS FOR OSCILLATOR A

  oscAGroup = cp5.addGroup("Oscillator A")
    .setPosition(20, 100)
    .disableCollapse();

  oscAWaveformKnob = cp5.addKnob("OscAWaveformKnob")
    .setRange(0, 5)
    .setValue(0)
    .setPosition(0, 10)
    .setRadius(35)
    .setNumberOfTickMarks(5)
    .setTickMarkLength(4)
    .snapToTickMarks(true)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Waveform Select")
    .setGroup(oscAGroup)
    ;

  oscAVolumeKnob = cp5.addKnob("OscAVolumeKnob")
    .setRange(0, 10)
    .setValue(5)
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

  oscBWaveformKnob = cp5.addKnob("OscBWaveformKnob")
    .setRange(0, 5)
    .setValue(0)
    .setPosition(0, 10)
    .setRadius(35)
    .setNumberOfTickMarks(5)
    .setTickMarkLength(4)
    .snapToTickMarks(true)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Osc B Waveform")
    .setGroup(oscBGroup)
    ;

  oscBVolumeKnob = cp5.addKnob("OscBVolumeKnob")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(100, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("Volume")
    .setGroup(oscBGroup)
    ;

  oscBDetuneKnob = cp5.addKnob("OscBDetuneKnob")
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

  lfoOnOffButton = cp5.addButton("LFOOnOffButton")
    .setPosition(0, 10)
    .setValue(0)
    .setSize(80, 80)
    .setGroup(lfoGroup)
    ;

  lfoDestKnob = cp5.addKnob("LFODestKnob")
    .setRange(0, 3)
    .setValue(0)
    .setPosition(100, 10)
    .setRadius(35)
    .setNumberOfTickMarks(3)
    .snapToTickMarks(true)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Destination")
    .setGroup(lfoGroup)
    ;

  lfoRateKnob = cp5.addKnob("LFORateKnob")
    .setRange(0, 10)
    .setValue(0)
    .setPosition(200, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Rate")
    .setGroup(lfoGroup)
    ;

  lfoAmountKnob = cp5.addKnob("LFOAmountKnob")
    .setRange(0, 10)
    .setValue(5)
    .setPosition(300, 10)
    .setRadius(35)
    .setDragDirection(Knob.VERTICAL)
    .setLabel("LFO Amount")
    .setGroup(lfoGroup)
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
