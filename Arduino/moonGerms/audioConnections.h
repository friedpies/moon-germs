
// GUItool: begin automatically generated code
AudioSynthWaveform       oscillatorA;      //xy=97,91
AudioSynthWaveform       oscillatorB;      //xy=98,147
AudioSynthNoisePink      pinkNoise;          //xy=99,207
AudioMixer4              mixer;         //xy=279,138
AudioFilterStateVariable lpFilter;        //xy=415,136
AudioEffectEnvelope      envelope;      //xy=553,134
AudioOutputI2S           i2s;           //xy=728,132
AudioConnection          patchCord1(oscillatorA, 0, mixer, 0);
AudioConnection          patchCord2(oscillatorB, 0, mixer, 1);
AudioConnection          patchCord3(pinkNoise, 0, mixer, 2);
AudioConnection          patchCord4(mixer, 0, lpFilter, 0);
AudioConnection          patchCord5(lpFilter, 0, envelope, 0);
AudioConnection          patchCord6(envelope, 0, i2s, 0);
AudioConnection          patchCord7(envelope, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=338,218
// GUItool: end automatically generated code

