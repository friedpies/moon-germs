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
  //oscAWaveformRadioButton.setValue(oscAWaveform);
  oscAVolumeKnob.setValue(oscAVolume);
  //oscBWaveformRadioButton.setValue(oscBWaveform);
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
