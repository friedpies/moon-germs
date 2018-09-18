
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=175,227
AudioMixer4              mixer1;         //xy=478,283
AudioOutputI2S           i2s1;           //xy=717,277
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, 0, i2s1, 0);
AudioConnection          patchCord3(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=322,441
// GUItool: end automatically generated code

