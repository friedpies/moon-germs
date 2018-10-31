// updates all parameters from bank when device cycles through banks
void updateAllVariablesFromBank(int bank) {
  if (!isConnected) {
    updateCurrentAnimation(bank);
  }
  AudioNoInterrupts();
  sgtl5000_1.volume(MasterVolume[bank]);

  oscillatorA.begin(OscAWaveform[bank]);
  oscillatorA.amplitude(OscAVolume[bank]);

  oscillatorB.begin(OscBWaveform[bank]);
  oscillatorB.amplitude(OscBVolume[bank]);

  filterModulationMixer.gain(0, LFOOnOff[bank]);
  LFOsine.frequency(LFORate[bank]);
  LFOsine.amplitude(LFOAmount[bank]);

  filterBypassMixer.gain(0, !FilterOnOff[bank]);
  filterBypassMixer.gain(1, FilterOnOff[bank]);
  filter.resonance(FilterQ[bank]);
  filter.frequency(FilterCutoff[bank]);
  ampEnvelope.attack(AmpAttack[bank]);
  ampEnvelope.release(AmpRelease[bank]);
  //  animationLength = AnimationLength[bank];
  //  updateCurrentAnimation(squareWaveBMP, animationLength);
  AudioInterrupts();
}

// Function to parse incoming data from Desktop app and adjust parameters in real time
void updateGlobalVariable(String parameter, String value) {
  AudioNoInterrupts();
  if (parameter == "masterVolume") {
    MasterVolume[bank] = value.toFloat();
    sgtl5000_1.volume(MasterVolume[bank]);
  }
  else if (parameter == "oscAWaveform") {
    OscAWaveform[bank] = value.toInt(); // cast string into integer (enum) value
    oscillatorA.begin(OscAWaveform[bank]);
  }
  else if (parameter == "oscAVolume") {
    OscAVolume[bank] = value.toFloat();
    oscillatorA.amplitude(OscAVolume[bank]);
  }
  else if (parameter == "oscBWaveform") {
    OscBWaveform[bank] = value.toInt(); // cast string into integer (enum) value
    oscillatorB.begin(OscBWaveform[bank]);
  }
  else if (parameter == "oscBVolume") {
    OscBVolume[bank] = value.toFloat();
    oscillatorB.amplitude(OscBVolume[bank]);
  }
  else if (parameter == "oscBDetune") {
    OscBDetune[bank] = value.toFloat();
  }
  else if (parameter == "noiseVolume") {
    NoiseVolume[bank] = value.toFloat();
  }
  else if (parameter == "lfoOnOff") {
    LFOOnOff[bank] = value.toInt();
    filterModulationMixer.gain(0, LFOOnOff[bank]);
  }
  else if (parameter == "lfoRate") {
    LFORate[bank] = value.toFloat();
    //    LFOsine.frequency(LFORate[bank]); // this is updated by IRSensor()
  }
  else if (parameter == "lfoAmount") {
    LFOAmount[bank] = value.toFloat();
  }
  else if (parameter == "filterOnOff") {
    FilterOnOff[bank] = value.toInt();
    filterBypassMixer.gain(0, !FilterOnOff[bank]);
    filterBypassMixer.gain(1, FilterOnOff[bank]);
  }
  else if (parameter == "filterQ") {
    FilterQ[bank] = value.toFloat();
    filter.resonance(FilterQ[bank]);
  }
  else if (parameter == "filterCutoff") {
    FilterCutoff[bank] = value.toFloat();
    filter.frequency(FilterCutoff[bank]);
  }
  else if (parameter == "triggerDest") { // Trigger Destination is as follows {OSC B DETUNE, FILTER CUTOFF, LFO RATE, LFO AMOUNT};
    for (int i = 0; i < value.length(); i++) {
      TriggerDest[bank][i] = value[i] - '0'; // convert char to integer value
    }

    if (TriggerDest[bank][1]) {
      filterBypassMixer.gain(0, 0.0); // if FILTER CUTOFF, TURN FILTER ON
      filterBypassMixer.gain(1, 1.0);
    }
    if (TriggerDest[bank][2] || TriggerDest[bank][3]) { // if LFO RATE OR LFO AMOUNT, TURN LFO ON and FILTER ON
      filterBypassMixer.gain(0, 0.0);
      filterBypassMixer.gain(1, 1.0);
      filterModulationMixer.gain(0, 1.0);
    }
  }
  else if (parameter == "ampAttack") {
    AmpAttack[bank] = value.toInt();
    ampEnvelope.attack(AmpAttack[bank]);
  }
  else if (parameter == "ampRelease") {
    AmpRelease[bank] = value.toInt();
    ampEnvelope.release(AmpRelease[bank]);
  }
  AudioInterrupts();
}

