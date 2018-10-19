void updateGlobalVariable(String parameter, String value) {

  if (parameter == "pressPlay") {
    pressPlay = value.toInt(); // cast string into integer value
    if (pressPlay) {
      ampEnvelope.noteOn();
      filterEnvelope.noteOn();
    } else {
      ampEnvelope.noteOff();
      filterEnvelope.noteOff();
    }
  }
  else if (paramter =="masterVolume"){
    masterVolume = value.toFloat();
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
  else if (parameter == "noiseVolume"){
    noiseVolume = value.toFloat();
    pinkNoise.amplitude(noiseVolume);
  }
  else if (parameter == "lfoOnOff"){
    
  }
  else if (parameter == "lfoRate"){
    
  }
  else if (parameter == "lfoAmount"){
    
  }
  else if (parameter == "lfoDest"){
    
  }
  else if (parameter == "filterOnOff"){
    
  }
  else if (parmaeter == "filterQ"){
    
  }
  else if (parameter == "filterCutoff"){
    
  }
  else if (parameter == "filterAttack"){
    
  }
  else if (paramter == "filterRelease"){
    
  }
  else if (parameter == "triggerDest"){
    
  }
  else if (parameter == "ampAttack"){
    
  }
  else if (parameter == "ampRelease"){
    
  }
}

