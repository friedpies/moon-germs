// GUItool: begin automatically generated code
AudioSynthWaveform       oscillatorA;      //xy=271,70
AudioSynthWaveform       oscillatorB;      //xy=271,125
AudioSynthWaveformSine   LFOsine;          //xy=277,203
AudioMixer4              waveformMixer;         //xy=480,101
AudioMixer4              filterModulationMixer;         //xy=484,208
AudioFilterStateVariable filter;        //xy=677,129
AudioEffectEnvelope      ampEnvelope;      //xy=814,225
AudioMixer4              filterBypassMixer;         //xy=862,85
AudioOutputI2S           i2s;           //xy=1026,224
AudioAnalyzeFFT256       fft256_1;       //xy=1027,303
AudioConnection          patchCord1(oscillatorA, 0, waveformMixer, 0);
AudioConnection          patchCord2(oscillatorB, 0, waveformMixer, 1);
AudioConnection          patchCord3(LFOsine, 0, filterModulationMixer, 0);
AudioConnection          patchCord4(waveformMixer, 0, filterBypassMixer, 0);
AudioConnection          patchCord5(waveformMixer, 0, filter, 0);
AudioConnection          patchCord6(filterModulationMixer, 0, filter, 1);
AudioConnection          patchCord7(filter, 0, filterBypassMixer, 1);
AudioConnection          patchCord8(ampEnvelope, 0, i2s, 0);
AudioConnection          patchCord9(ampEnvelope, 0, i2s, 1);
AudioConnection          patchCord10(ampEnvelope, fft256_1);
AudioConnection          patchCord11(filterBypassMixer, ampEnvelope);
AudioControlSGTL5000     sgtl5000_1;     //xy=492,313
// GUItool: end automatically generated code

