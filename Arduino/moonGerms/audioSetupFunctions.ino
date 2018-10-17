// intialize audio variables

void setupAudio() {
  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  oscillatorA.begin(waveformType);
  oscillatorA.amplitude(0.75);
  oscillatorA.frequency(centerFreq);
  oscillatorA.pulseWidth(0.5);

  oscillatorB.begin(waveformType);
  oscillatorB.amplitude(0.75);
  oscillatorB.frequency(centerFreq);
  oscillatorB.pulseWidth(0.15);

  pinkNoise.amplitude(1.0);

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

