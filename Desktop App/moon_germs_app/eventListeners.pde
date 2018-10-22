void serialEvent(Serial mgPort) {
  incomingData = mgPort.readString();
  println("SERIAL EVENT: " + incomingData);

  String dataType = incomingData.substring(0, 4); // Check if incoming data contains information from Buttons Presses, Bank changes, Trigger Info, and Display Info, LOAD data etc.
  int bank;
  switch (dataType) {
  case "CONN":
    println("CONNECTED");
    connectionToggle.setValue(1.0);
    isDeviceConnected = true;
    incomingData = "";
    mgPort.write("L~"); // auto Load data
    break;
  case "LOAD":
    bank = int(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    bankIndex = bank;
    parseData(incomingData);
    incomingData = "";
    break;
  case "BUTT":
    String buttonSubstring = incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1);
    int button = buttonSubstring.charAt(0) - '0';
    boolean value = boolean(buttonSubstring.charAt(1) - '0');
    buttonDisplays[button] = value;
    incomingData = "";
    break;

  case "BANK":
    bank = int(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    bankIndex = bank;
    updateGui(
      MasterVolume[bankIndex], 
      OscAWaveform[bankIndex], 
      OscAVolume[bankIndex], 
      OscBWaveform[bankIndex], 
      OscBVolume[bankIndex], 
      OscBDetune[bankIndex], 
      NoiseVolume[bankIndex], 
      LFOOnOff[bankIndex], 
      LFORate[bankIndex], 
      LFOAmount[bankIndex], 
      LFODest[bankIndex], 
      FilterOnOff[bankIndex], 
      FilterQ[bankIndex], 
      FilterCutoff[bankIndex], 
      TriggerDest[bankIndex][0], 
      TriggerDest[bankIndex][1], 
      TriggerDest[bankIndex][2], 
      TriggerDest[bankIndex][3], 
      AmpAttack[bankIndex], 
      AmpRelease[bankIndex]
      );
    //bankNumberbox.setValue(bank);
    incomingData = "";
    break;

  case "TRIG":
    int triggerValue = int(incomingData.substring(incomingData.indexOf(',') + 1, incomingData.length() - 1));
    triggerDelta = int(map(triggerValue, 1019, 524, 0, 30));
    break;
  }
}

// Event listener for all controller events
void controlEvent(ControlEvent e) { 
  if (e.isFrom(comPortList)) { // if dropdown list has been clicked
    if (isDeviceConnected) { // clear and stop existing serial port if device is connected
      mgPort.clear();
      mgPort.stop();
    }
    portName = Serial.list()[int(e.getValue())]; // Connect to device
    mgPort = new Serial(this, portName, 115200);
    mgPort.bufferUntil('~');
    mgPort.write("C~");
  } else if (e.isFrom(connectionToggle)) {
    if (e.getValue() == 0.0) {
      mgPort.write("D~");
      mgPort.clear();
      mgPort.stop();
      isDeviceConnected = false;
      //println(e.getValue());
    }
  } else if (e.isFrom(closeButton)) {
    if (isDeviceConnected) {
      mgPort.write("D~");
    }
    exit();
  } else if (e.isFrom(loadButton)) {
    if (isDeviceConnected) {
      mgPort.write("L~");
      //appState = "LOADING";
    }
  } else {
    if (isDeviceConnected) {
      String value = "";
      if (e.isFrom(triggerDestCheckBox)) { // if click is from checkbox, send array
        float[] checkBoxArray = e.getArrayValue();
        for (int i = 0; i < checkBoxArray.length; i++) {
          value = value + str(int(checkBoxArray[i])); // send string of 4 bits representing each check box
        }
      } else if (isDeviceConnected) {
        value = str(e.getValue());
      }
      mgPort.write(e.getName() + "," + value + "~");
    }
  }
}

void stop() {
  if (isDeviceConnected) {
    mgPort.write("DISCONNECT~");
  }
}
