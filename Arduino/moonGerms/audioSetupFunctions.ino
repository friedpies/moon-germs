// intialize audio variables

void setupAudio() {
  /////////////////////////////////////////////
  //Set up presets at Bank 0

  MasterVolume[0] = 0.32;

  OscAWaveform[0] = WAVEFORM_SAWTOOTH;
  OscAVolume[0] = 0.75;

  OscBWaveform[0] = WAVEFORM_SAWTOOTH;
  OscBVolume[0] = 0.75;
  OscBDetune[0] - 1.0;

  NoiseVolume[0] = 0.0;

  LFOOnOff[0] = false; // volume of filterMod Mixer
  LFORate[0] = 0; // hertz
  LFOAmount[0] = 0.0;
  LFODest[0] = 0; // might get rid of this


  FilterOnOff[0] = false;
  FilterQ[0] = 0.707; // range from 0.7 to 5;
  FilterCutoff[0] = 10000; // Hertz

//  TriggerDest[0] = 0;
  AmpAttack[0] = 0.0; //ms
  AmpRelease[0] = 0.0; //ms

  ///////////////////////////////////////////////////////

  AudioMemory(40);
  sgtl5000_1.enable();
  sgtl5000_1.volume(MasterVolume[0]);

  oscillatorA.begin(OscAWaveform[0]);
  oscillatorA.amplitude(OscAVolume[0]);
  oscillatorA.frequency(centerFreq);

  oscillatorB.begin(OscBWaveform[0]);
  oscillatorB.amplitude(OscBVolume[0]);
  oscillatorB.frequency(centerFreq);

  pinkNoise.amplitude(NoiseVolume[0]);

  // combine waveforms (these will not change)
  waveformMixer.gain(0, 1.0); // Osc A
  waveformMixer.gain(1, 1.0); // Osc B
  waveformMixer.gain(2, 1.0); // pink Noise

  filterModulationMixer.gain(0, int(LFOOnOff[0])); // turns LFO on or Off
  LFOsine.frequency(LFORate[0]);
  LFOsine.amplitude(LFOAmount[0]);

  filterBypassMixer.gain(0, int(!FilterOnOff[0]));
  filterBypassMixer.gain(1, int(FilterOnOff[0]));
  filter.resonance(FilterQ[0]);
  filter.frequency(FilterCutoff[0]);
  filter.octaveControl(2);

  // ADSR Params
  ampEnvelope.attack(AmpAttack[0]);
  ampEnvelope.sustain(1.0); //gain of 1.0
  ampEnvelope.release(AmpRelease[0]);

}

