void checkButton1(){
  if (button1.fallingEdge()) {
    Serial.println("hello");
    matrix.clear();
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
//    oscillatorA.begin(1.0, 220, waveform_type);
//    deviceState = PLAY_STATE;
  envelope.noteOn();
  } else if (button1.risingEdge()) {
    matrix.clear();
    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
//    oscillatorA.begin(0.0, 220, waveform_type);
//    deviceState = IDLE_STATE;
envelope.noteOff();
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
    oscillatorA.begin(waveform_type);
  }
}

float checkTrigger(){
  triggerRead = analogRead(TRIGGER);
  triggerRead = map(triggerRead, 50, 900, 0, 1000);
  if (triggerRead < 0) {
    triggerRead = 0;
  }
//  Serial.println(triggerRead);
  lpFilter.frequency(triggerRead * 10);
//  return float(triggerRead) * 0.001;
}

float checkIR(){
  infraredRead = analogRead(IR_SENSOR);
  if (infraredRead < 0) {
    infraredRead = 0;
  }
  if (infraredRead > 4000){
    infraredRead = 4000;
  }
//  Serial.println(infraredRead);
//  lpFilter.frequency(infraredRead);
  return infraredRead;
}


