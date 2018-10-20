// updates all parameters from bank when device cycles through banks
void updateAllVariablesFromBank(int bank) {
  AudioNoInterrupts();
  sgtl5000_1.volume(MasterVolume[bank]);

  oscillatorA.begin(OscAWaveform[bank]);
  oscillatorA.amplitude(OscAVolume[bank]);

  oscillatorB.begin(OscBWaveform[bank]);
  oscillatorB.amplitude(OscBVolume[bank]);

  pinkNoise.amplitude(NoiseVolume[bank]);

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
  if (parameter == "playPause") {
    playPause = value.toInt(); // cast string into integer value
    pressPlay = playPause;
    pressPause = !playPause;
  }
  else if (parameter == "masterVolume") {
    masterVolume = value.toFloat();
    sgtl5000_1.volume(masterVolume);
  }
  else if (parameter == "oscAWaveform") {
    oscAWaveform = value.toInt(); // cast string into integer (enum) value
    oscillatorA.begin(oscAWaveform);
  }
  else if (parameter == "oscAVolume") {
    oscAVolume = value.toFloat();
    oscillatorA.amplitude(oscAVolume);
  }
  else if (parameter == "oscBWaveform") {
    oscBWaveform = value.toInt(); // cast string into integer (enum) value
    oscillatorB.begin(oscBWaveform);
  }
  else if (parameter == "oscBVolume") {
    oscBVolume = value.toFloat();
    oscillatorB.amplitude(oscBVolume);
  }
  else if (parameter == "oscBDetune") {
    // do something
  }
  else if (parameter == "noiseVolume") {
    noiseVolume = value.toFloat();
    pinkNoise.amplitude(noiseVolume);
  }
  else if (parameter == "lfoOnOff") {
    lfoOnOff = value.toInt();
    filterModulationMixer.gain(0, lfoOnOff);
  }
  else if (parameter == "lfoRate") {
    lfoRate = value.toFloat();
    LFOsine.frequency(lfoRate);
  }
  else if (parameter == "lfoAmount") {
    lfoAmount = value.toFloat();
    LFOsine.amplitude(lfoAmount);
  }
  else if (parameter == "lfoDest") {

  }
  else if (parameter == "filterOnOff") {
    filterOnOff = value.toInt();
    filterBypassMixer.gain(0, !filterOnOff);
    filterBypassMixer.gain(1, filterOnOff);
  }
  else if (parameter == "filterQ") {
    filterQ = value.toFloat();
    filter.resonance(filterQ);
  }
  else if (parameter == "filterCutoff") {
    filterCutoff = value.toFloat();
    filter.frequency(filterCutoff);
  }
  else if (parameter == "triggerDest") { // Trigger Destination is as follow {OSC B DETUNE, FILTER CUTOFF, LFO RATE, LFO AMOUNT};
    for (int i = 0; i < value.length(); i++) {
      triggerDest[i] = value[i] - '0'; // convert char to integer value
    }
    filterBypassMixer.gain(0, !triggerDest[1]);
    filterBypassMixer.gain(1, triggerDest[1]);
  }
  else if (parameter == "ampAttack") {
    ampAttack = value.toInt();
    ampEnvelope.attack(ampAttack);
  }
  else if (parameter == "ampRelease") {
    ampRelease = value.toInt();
    ampEnvelope.release(ampRelease);
  }
  AudioInterrupts();
}

