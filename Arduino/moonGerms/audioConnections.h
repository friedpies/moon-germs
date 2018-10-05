// GUItool for Teensy Audio: begin automatically generated code
// https://www.pjrc.com/teensy/gui/
AudioSynthWaveform       oscillatorA;      //xy=97,91
AudioSynthWaveform       oscillatorB;      //xy=98,147
AudioSynthNoisePink      pinkNoise;          //xy=99,207
AudioMixer4              mixer;         //xy=279,138
AudioEffectEnvelope      envelope;      //xy=553,134
AudioAmplifier           amp;           //xy=693,133
AudioOutputI2S           i2s;           //xy=832,131
AudioConnection          patchCord1(oscillatorA, 0, mixer, 0);
AudioConnection          patchCord2(oscillatorB, 0, mixer, 1);
AudioConnection          patchCord3(pinkNoise, 0, mixer, 2);
AudioConnection          patchCord4(mixer, envelope);
AudioConnection          patchCord5(envelope, amp);
AudioConnection          patchCord6(amp, 0, i2s, 0);
AudioConnection          patchCord7(amp, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=377,232
// GUItool: end automatically generated code

