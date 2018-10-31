// Functions to handle data from desktop app
void serialEvent() {
  incomingData = Serial.readStringUntil('~'); // this is useful for parameters updates
  char incomingChar = incomingData.charAt(0);
  switch (incomingChar) {
    case 'C': // C for connect
      Serial.print("CONN~");
      isConnected = true;
      playAnimation = true;
      updateAnimationConnect();
      break;
    case 'D': // D for disconnect
      playAnimation = false;
      matrix.clear();
      matrix.writeDisplay();
      updateCurrentAnimation(bank);
      isConnected = false;
      break;
    case 'L': // L for load
      sendAllData();
      break;
    case 'P': // P for parameter
      parameter = incomingData.substring(1, incomingData.indexOf(','));
      value = incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length());
      updateGlobalVariable(parameter, value);
      break;
  }
      incomingData = "";
}


