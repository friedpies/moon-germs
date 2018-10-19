// GUItool: begin automatically generated code
AudioSynthWaveformSine   LFOsine;          //xy=258,290
AudioSynthWaveform       oscillatorA;      //xy=271,70
AudioSynthWaveform       oscillatorB;      //xy=271,125
AudioSynthNoisePink      pinkNoise;          //xy=272,182
AudioMixer4              waveformMixer;         //xy=480,101
AudioMixer4              filterModulationMixer;         //xy=496,233
AudioFilterStateVariable filter;        //xy=677,129
AudioMixer4              filterBypassMixer;         //xy=862,85
AudioEffectEnvelope      ampEnvelope;      //xy=1025,168
AudioOutputI2S           i2s;           //xy=1310,85
AudioConnection          patchCord1(LFOsine, 0, filterModulationMixer, 0);
AudioConnection          patchCord2(oscillatorA, 0, waveformMixer, 0);
AudioConnection          patchCord3(oscillatorB, 0, waveformMixer, 1);
AudioConnection          patchCord4(pinkNoise, 0, waveformMixer, 2);
AudioConnection          patchCord5(waveformMixer, 0, filterBypassMixer, 0);
AudioConnection          patchCord6(waveformMixer, 0, filter, 0);
AudioConnection          patchCord7(filterModulationMixer, 0, filter, 1);
AudioConnection          patchCord8(filter, 0, filterBypassMixer, 1);
AudioConnection          patchCord9(filterBypassMixer, ampEnvelope);
AudioConnection          patchCord10(ampEnvelope, 0, i2s, 0);
AudioConnection          patchCord11(ampEnvelope, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=452,455
// GUItool: end automatically generated code

