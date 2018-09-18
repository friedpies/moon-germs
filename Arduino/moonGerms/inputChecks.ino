void checkButton1(){
  if (button1.fallingEdge()) {
    matrix.clear();
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
    waveform1.begin(1.0, 220, waveform_type);
    deviceState = PLAY_STATE;
  } else if (button1.risingEdge()) {
    matrix.clear();
    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
    waveform1.begin(0.0, 220, waveform_type);
    deviceState = IDLE_STATE;
  }
}

void checkButton2(){
  if (button2.fallingEdge()) {
    if (waveform_type == WAVEFORM_SAWTOOTH) {
      waveform_type = WAVEFORM_SINE;
    } else if (waveform_type == WAVEFORM_SINE) {
      waveform_type = WAVEFORM_SQUARE;
    } else if (waveform_type == WAVEFORM_SQUARE) {
      waveform_type = WAVEFORM_TRIANGLE;
    } else if (waveform_type ==
    WAVEFORM_TRIANGLE) {
      waveform_type = WAVEFORM_PULSE;
    } else if (waveform_type == WAVEFORM_PULSE) {
      waveform_type = WAVEFORM_SAWTOOTH;
    }
    waveform1.begin(waveform_type);
  }
}

float checkTrigger(){
  triggerRead = analogRead(TRIGGER);
  triggerRead = map(triggerRead, 50, 900, 0, 1000);
  if (triggerRead < 0) {
    triggerRead = 0;
  }
  return float(triggerRead) * 0.001;
}

int checkIR(){
  infraredRead = analogRead(IR_SENSOR);
  Serial.println(infraredRead);
  infraredRead = map(infraredRead, 60, 800, 300, 100);
  if (infraredRead < 0) {
    infraredRead = 0;
  }
  return infraredRead;
}


