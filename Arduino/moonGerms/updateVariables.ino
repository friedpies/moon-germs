void updateGlobalVariable(String parameter, String value) {

  if (parameter == "pressPlay") {
    pressPlay = value.toInt(); // cast string into integer value
    if (pressPlay) {
      oscillatorA.frequency(100);
      oscillatorB.frequency(100);
      ampEnvelope.noteOn();
    } else {
      ampEnvelope.noteOff();
    }
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
  else if (parameter == "triggerDest") {

  }
  else if (parameter == "ampAttack") {
    ampAttack = value.toInt();
    ampEnvelope.attack(ampAttack);
  }
  else if (parameter == "ampRelease") {
    ampRelease = value.toInt();
    ampEnvelope.release(ampRelease);
  }
}

