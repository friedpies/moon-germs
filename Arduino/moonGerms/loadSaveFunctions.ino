// Function to send all stored data to desktop app
void sendAllData() {
  //  delay(100);
  //  Serial.print("LOADING" + '\n');
  int i;
  Serial.print("LOAD," + String(bank) + "\n");
  for (i = 0; i < numberOfBanks; i++) {
    Serial.print("bank:" + String(i) + '\n');
    Serial.print("masterVolume:" + String(MasterVolume[i]) + '\n');

    Serial.print("oscAWaveform:" + String(OscAWaveform[i]) + '\n');
    Serial.print("oscAVolume:" + String(OscAVolume[i]) + '\n');

    Serial.print("oscBWaveform:" + String(OscBWaveform[i]) + '\n');
    Serial.print("oscBVolume:" + String(OscBVolume[i]) + '\n');
    Serial.print("oscBDetune:" + String(OscBDetune[i]) + '\n');

    Serial.print("noiseVolume:" + String(NoiseVolume[i]) + '\n');

    Serial.print("lfoOnOff:" + String(LFOOnOff[i]) + '\n');
    Serial.print("lfoRate:" + String(LFORate[i]) + '\n');
    Serial.print("lfoAmount:" + String(LFOAmount[i]) + '\n');
    Serial.print("lfoDest:" + String(LFODest[i]) + '\n');

    Serial.print("filterOnOff:" + String(FilterOnOff[i]) + '\n');
    Serial.print("filterQ:" + String(FilterQ[i]) + '\n');
    Serial.print("filterCutoff:" + String(FilterCutoff[i]) + '\n');

    for (int j = 0; j < 4; j++) {
      Serial.print("triggerDest" + String(j) + ':' + String(TriggerDest[i][j]) + '\n');
    }

    Serial.print("ampAttack:" + String(AmpAttack[i]) + '\n');
    Serial.print("ampRelease:" + String(AmpRelease[i]) + '\n');
  }
  Serial.print("bank:" + String(i) + '~');
}

