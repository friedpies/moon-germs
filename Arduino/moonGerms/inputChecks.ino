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
      case WAVEFORM_SAWTOOTH_REVERSE:
        waveformType = WAVEFORM_SQUARE;
        animationLength = squareWaveBMPSize; //animation data stored in bitMaps.h
        updateCurrentAnimation(squareWaveBMP, animationLength);
        currentFrame = 0;
        displayColor = LED_YELLOW;
        break;

      case WAVEFORM_SQUARE:
        waveformType = WAVEFORM_TRIANGLE;
        animationLength = triangleWaveBMPSize;
        updateCurrentAnimation(triangleWaveBMP, animationLength);
        currentFrame = 0;
        displayColor = LED_RED;
        break;

      case WAVEFORM_TRIANGLE:
        waveformType = WAVEFORM_SINE;
        animationLength = sineWaveBMPSize;
        updateCurrentAnimation(sineWaveBMP, animationLength);
        currentFrame = 0;
        displayColor = LED_GREEN;
        break;

      case WAVEFORM_SINE:
        waveformType = WAVEFORM_SAWTOOTH;
        animationLength = sawWaveBMPSize;
        updateCurrentAnimation(sawWaveBMP, animationLength);
        currentFrame = 0;
        displayColor = LED_YELLOW;
        break;

      case WAVEFORM_SAWTOOTH:
        waveformType = WAVEFORM_SAWTOOTH_REVERSE;
        animationLength = sawWaveReverseBMPSize;
        updateCurrentAnimation(sawWaveReverseBMP, animationLength);
        currentFrame = 0;
        displayColor = LED_RED;
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
    if (frameRate > 100) {
      frameRate = 100;
    }
    if (frameRate < 10) {
      frameRate = 10;
    }
    oscillatorA.frequency(globalFreq); 
    oscillatorB.frequency(globalFreq * detune);
    readIndex = 0;
    readingAverage = 0;
  }
}

//
void readTrigger() { // apply detune to Oscillator 2
  triggerRead = analogRead(TRIGGER);
  detune = map(float(triggerRead), 0, 1023, 1.2, 1);
}
