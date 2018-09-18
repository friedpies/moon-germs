// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=305,238
AudioSynthWaveformSine   sine1;          //xy=319,296
AudioMixer4              mixer1;         //xy=500,299
AudioOutputI2S           i2s1;           //xy=868,299
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(sine1, 0, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=322,441
// GUItool: end automatically generated code

