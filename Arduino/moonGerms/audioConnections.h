// GUItool: begin automatically generated code
AudioSynthWaveform       oscillatorA;      //xy=97,91
AudioSynthWaveform       oscillatorB;      //xy=98,147
AudioSynthNoisePink      pinkNoise;          //xy=99,207
AudioMixer4              mixer;         //xy=279,138
AudioFilterStateVariable lpFilter;        //xy=415,136
AudioEffectEnvelope      envelope;      //xy=553,134
AudioAmplifier           amp;           //xy=704,135
AudioOutputI2S           i2s;           //xy=1032,127
AudioConnection          patchCord1(oscillatorA, 0, mixer, 0);
AudioConnection          patchCord2(oscillatorB, 0, mixer, 1);
AudioConnection          patchCord3(pinkNoise, 0, mixer, 2);
AudioConnection          patchCord4(mixer, 0, lpFilter, 0);
AudioConnection          patchCord5(lpFilter, 0, envelope, 0);
AudioConnection          patchCord6(envelope, amp);
AudioConnection          patchCord7(amp, 0, i2s, 0);
AudioConnection          patchCord8(amp, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=377,232
// GUItool: end automatically generated code
