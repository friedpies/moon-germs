// GUItool: begin automatically generated code
AudioSynthWaveformDc     filterDCSignal;            //xy=158,268
AudioSynthWaveformSine   LFOsine;          //xy=161,327
AudioSynthWaveform       oscillatorA;      //xy=271,70
AudioSynthWaveform       oscillatorB;      //xy=271,125
AudioSynthNoisePink      pinkNoise;          //xy=272,182
AudioMixer4              filterModulationMixer;         //xy=369,299
AudioMixer4              waveformMixer;         //xy=480,101
AudioEffectEnvelope      filterEnvelope;      //xy=540,202
AudioFilterStateVariable filter;        //xy=676,129
AudioMixer4              filterBypassMixer;         //xy=862,85
AudioEffectEnvelope      ampEnvelope;      //xy=1025,168
AudioOutputI2S           i2s;           //xy=1310,85
AudioConnection          patchCord1(filterDCSignal, 0, filterModulationMixer, 0);
AudioConnection          patchCord2(LFOsine, 0, filterModulationMixer, 1);
AudioConnection          patchCord3(oscillatorA, 0, waveformMixer, 0);
AudioConnection          patchCord4(oscillatorB, 0, waveformMixer, 1);
AudioConnection          patchCord5(pinkNoise, 0, waveformMixer, 2);
AudioConnection          patchCord6(filterModulationMixer, filterEnvelope);
AudioConnection          patchCord7(waveformMixer, 0, filterBypassMixer, 0);
AudioConnection          patchCord8(waveformMixer, 0, filter, 0);
AudioConnection          patchCord9(filterEnvelope, 0, filter, 1);
AudioConnection          patchCord10(filter, 0, filterBypassMixer, 1);
AudioConnection          patchCord11(filterBypassMixer, ampEnvelope);
AudioConnection          patchCord12(ampEnvelope, 0, i2s, 0);
AudioConnection          patchCord13(ampEnvelope, 0, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=452,455
// GUItool: end automatically generated code

