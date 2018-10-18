// intialize audio variables

void setupAudio() {
  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  oscillatorA.begin(waveformType);
  oscillatorA.amplitude(oscAVolume);
  oscillatorA.frequency(centerFreq);
//  oscillatorA.pulseWidth(0.5);

  oscillatorB.begin(waveformType);
  oscillatorB.amplitude(oscBVolume);
  oscillatorB.frequency(centerFreq);
//  oscillatorB.pulseWidth(0.5);

  pinkNoise.amplitude(0);

  mixer.gain(0, 1.0); // Osc A
  mixer.gain(1, 1.0); // Osc B
  mixer.gain(2, 0.1); // pink Noise

  // ADSR Params
  envelope.attack(100);
  envelope.decay(0);
  envelope.sustain(1.0);
  envelope.release(200);

  amp.gain(6);
}

