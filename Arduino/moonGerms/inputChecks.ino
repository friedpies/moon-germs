//
//void checkButton2() {
//  if (button2.fallingEdge()) {
//    if (waveformType == WAVEFORM_SAWTOOTH) {
//      waveformType = WAVEFORM_SINE;
//    } else if (waveformType == WAVEFORM_SINE) {
//      waveformType = WAVEFORM_SQUARE;
//    } else if (waveformType == WAVEFORM_SQUARE) {
//      waveformType = WAVEFORM_TRIANGLE;
//    } else if (waveformType ==
//               WAVEFORM_TRIANGLE) {
//      waveformType = WAVEFORM_PULSE;
//    } else if (waveformType == WAVEFORM_PULSE) {
//      waveformType = WAVEFORM_SAWTOOTH;
//    }
//    oscillatorA.begin(waveformType);
//  }
//}

float checkTrigger() {
  triggerRead = analogRead(TRIGGER);
  triggerRead = map(triggerRead, 50, 900, 0, 1000);
  if (triggerRead < 0) {
    triggerRead = 0;
  }
  //  Serial.println(triggerRead);
  lpFilter.frequency(triggerRead * 10);
    return float(triggerRead) * 0.001;
}



