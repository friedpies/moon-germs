// Functions to read each input perform corresponding action


// Play note when button 1 is depressed, stop note when released
void readButton1() {
  if (button1.fallingEdge()) {
    playAnimation = true;
    ampEnvelope.noteOn();
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTTON,01~");
    }
  } else if (button1.risingEdge() ) {
    ampEnvelope.noteOff();
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTTON,00~");
    }
    if (!isConnected) {
      playAnimation = false;
      matrix.clear();
      matrix.drawBitmap(0, 0, emptyBMP, 8, 8, displayColor);
      matrix.writeDisplay();
    }
  }
}


// Cycle through banks when button 2 is pressed
void readButton2() {
  if (button2.fallingEdge()) {
    bank++;
    if (bank > (numberOfBanks - 1)) {
      bank = 0;
    }
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTT,11~");
      Serial.print("BANK," + String(bank) + '~');
    }
    updateAllVariablesFromBank(bank);
  } else if (button2.risingEdge()) {
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTTON,10~");
    }
  }
}

// Increase Octave if button 3 is pressed
void readButton3() {
  if (button3.fallingEdge()) {
    octaveCounter++;
    if (octaveCounter > 4) {
      octaveCounter = 4;
    }
    centerFreq = noteA[octaveCounter];
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTT,21~");
    }
  }
  else if (button3.risingEdge()) {
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTT,20~");
    }
  }
}

// Decrease Octave if button 4 is pressed
void readButton4() {
  if (button4.fallingEdge()) {
    octaveCounter--;
    if (octaveCounter < 1) {
      octaveCounter = 1;
    }
    centerFreq = noteA[octaveCounter];
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTT,31~");
    }
  } else if (button4.risingEdge()) {
    if (isConnected) { // send button status to app if connected
      Serial.print("BUTT,30~");
    }
  }
}

// Take "numReadings" readings from IR sensor and average to smooth out signal, map signal to "bendFactor" multiplier and attenuate oscillator frequencies accordingly
void readIRSensor() { // This function dynamically updates sound when playing, all "real time" changes happen here
  infraredReadings[readIndex] = analogRead(IR_SENSOR);
  readIndex++;

  // Smoothing function for analog Read
  if (readIndex == numReadings) {
    for (int i = 0; i < numReadings; i++) {
      readingAverage = readingAverage + infraredReadings[i];
    }
    readingAverage = readingAverage / numReadings;
    mappedAverage = mapIRtoFloat(readingAverage);
    bendFactor = pow(2, mappedAverage);
    globalFreq = centerFreq * bendFactor;
    frameRate = map(globalFreq, 27.5, 1000, 100, 10);
    if (frameRate > 100) {
      frameRate = 100;
    }
    if (frameRate < 10) {
      frameRate = 10;
    }
    filter.frequency(FilterCutoff[bank] * (1 + (TriggerDest[bank][1] * pow(2, cutoffTrig)))); // for dynamic filter change, filter must be ON and Trigger Dest --> Filter must be "1"
    LFOsine.frequency(LFORate[bank] * (1 + (TriggerDest[bank][2] * rateTrig)));
    LFOsine.amplitude(LFOAmount[bank] * (1 + (TriggerDest[bank][3] * amountTrig)));
    oscillatorA.frequency(globalFreq);
    oscillatorB.frequency(OscBDetune[bank] * (globalFreq * (1 + (TriggerDest[bank][0] * detuneTrig)))); // TriggerDest[bank][0] corresponds to detune being on or off
    readIndex = 0;
    readingAverage = 0;
  }
}

//
void readTrigger() { // apply detune to Oscillator 2
  triggerRead = analogRead(TRIGGER);
  detuneTrig = map(float(triggerRead), 0, 1023, 1.2, 1);
  cutoffTrig = map(float(triggerRead), 0, 1023, 4, 1); // same scaling for filter cutoff, 4 octave range
  rateTrig = map(float(triggerRead), 0, 1023, 10, 1);
  amountTrig = map(float(triggerRead), 0, 1023, 5, 1);

  if ((abs(triggerRead - previousTriggerRead) > 5) && (isConnected)) {
    previousTriggerRead = triggerRead;
    Serial.print("TRIG," + String(triggerRead) + '~');
  }
}
