// Functions to read each input perform corresponding action


// Play note when button 1 is depressed, stop note when released
void readButton1() {
  if (button1.fallingEdge()) {
    playAnimation = true;
    envelope.noteOn();
  } else if (button1.risingEdge()) {
    playAnimation = false;
        matrix.clear();
    matrix.drawBitmap(0, 0, emptyBMP, 8, 8, displayColor);
    matrix.writeDisplay();
    envelope.noteOff();
  }
}


// Cycle through waveform types when button 2 is depressed
void readButton2() {
  if (button2.fallingEdge()) {
    switch (waveformType) {
      case WAVEFORM_SAWTOOTH:
        waveformType = WAVEFORM_SQUARE;
        animationLength = sizeof(squareWaveBMP) / sizeof(squareWaveBMP[0]);
        updateCurrentAnimation(squareWaveBMP, animationLength);
        displayColor = LED_YELLOW;
        break;

      case WAVEFORM_SQUARE:
        waveformType = WAVEFORM_TRIANGLE;
               animationLength = sizeof(triangleWaveBMP) / sizeof(triangleWaveBMP[0]);
               updateCurrentAnimation(triangleWaveBMP, animationLength);
        displayColor = LED_RED;
        break;

      case WAVEFORM_TRIANGLE:
        waveformType = WAVEFORM_SINE;
        animationLength = sizeof(sineWaveBMP) / sizeof(sineWaveBMP[0]);
        updateCurrentAnimation(sineWaveBMP, animationLength);
        displayColor = LED_YELLOW;
        break;

      case WAVEFORM_SINE:
        waveformType = WAVEFORM_SAWTOOTH;
                animationLength = sizeof(sawWaveBMP) / sizeof(sawWaveBMP[0]);
                updateCurrentAnimation(sawWaveBMP, animationLength);
        displayColor = LED_GREEN;
        break;
    }
    AudioNoInterrupts();
    oscillatorA.begin(waveformType);
    oscillatorB.begin(waveformType);
    AudioInterrupts();
  }
}

// Increase Octave if button 3 is pressed
void readButton3() {
  if (button3.fallingEdge()) {
    octaveCounter++;
    if (octaveCounter > 6) {
      octaveCounter = 6;
    }
    centerFreq = noteA[octaveCounter];
  }
  filterUpperBoundFreq = centerFreq * 2.0; // sets cutoff frequency to upper range of current octave
  filterLowerBoundFreq = centerFreq * 0.25;
}

// Decrease Octave if button 4 is pressed
void readButton4() {
  if (button4.fallingEdge()) {
    octaveCounter--;
    if (octaveCounter < 1) {
      octaveCounter = 1;
    }
    centerFreq = noteA[octaveCounter];
  }
  filterUpperBoundFreq = centerFreq * 2.0; // sets cutoff frequency to upper range of current octave
  filterLowerBoundFreq = centerFreq * 0.25;
}

// Take "numReadings" readings from IR sensor and average to smooth out signal, map signal to "bendFactor" multiplier and attenuate oscillator frequencies accordingly
void readIRSensor() {
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
    frameRate = map(globalFreq, 27.5, 1760, 100, 10);
    if (frameRate > 100){
      frameRate = 100;
    }
    if (frameRate < 10){
      frameRate = 10;
    }
    oscillatorA.frequency(globalFreq * 1.011); // 1.01 added for slight detune
    oscillatorB.frequency(globalFreq);
    readIndex = 0;
    readingAverage = 0;
  }
}

//
void readTrigger() {
  triggerRead = analogRead(TRIGGER);
  Serial.println(triggerRead);
  triggerRead = map(triggerRead, 0, 1023, filterLowerBoundFreq, filterUpperBoundFreq);
  if (triggerRead < filterLowerBoundFreq) {
    triggerRead = filterLowerBoundFreq;
  }
  //  //  Serial.println(triggerRead);
  lpFilter.frequency(triggerRead);
  //    return float(triggerRead) * 0.001;
}
