// updates values of buttons/knobs/sliders when bank is switched
void updateGui(
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
