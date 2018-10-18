void updateGlobalVariable(String parameter, String value) {

  if (parameter == "pressPlay") {
    pressPlay = value.toInt(); // cast string into integer value
    if (pressPlay) {
      envelope.noteOn();
    } else {
      envelope.noteOff();
    }
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
}

