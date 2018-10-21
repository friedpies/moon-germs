
// Function to "Pixelize" an image for aesthetic effect, wink to Teenage Engineering's website
void pixelateImage(int pixelWidth, PImage image) {
  int ratio = width/height;
  int pixelHeight = pixelWidth * ratio;
  for (int x = 0; x < width; x += pixelWidth) {
    for (int y = 0; y < height; y += pixelHeight) {
      fill(image.get(x, y));
      rect(x, y, pixelWidth, pixelHeight);
    }
  }
}

void splashSequence(float time1, float time2, float time3) {
  image(splashScreen, 0, 0); // show splash screen for X amount of time
  if (frameCount < (30 * time1)) {
    pixelateImage(15, splashScreen); // pixelates splashscreen image (for fun)
  } else if (frameCount < (30 * time2)) {
    pixelateImage(5, splashScreen);
  }
}

// Function to Parse data dump from device
void parseData(String loadData) {
  String[] dataPerBank = new String[numberOfBanks];

  for (int i = 0; i < numberOfBanks; i++) { // parse all incoming data into per-bank sections
    dataPerBank[i] = loadData.substring(loadData.indexOf("bank:" + str(i)), loadData.indexOf("bank:" + str(i + 1)));

    String[] splitData = split(dataPerBank[i], '\n'); // split up strings into individual variables

    // populate arrays with data, this needs to be refactored at some point
    MasterVolume[i] = float(splitData[1].substring((splitData[1].indexOf(':') + 1), splitData[1].length()));

    OscAWaveform[i] = int(splitData[2].substring((splitData[2].indexOf(':') + 1), splitData[2].length()));
    OscAVolume[i] = float(splitData[3].substring((splitData[3].indexOf(':') + 1), splitData[3].length()));

    OscBWaveform[i] = int(splitData[4].substring((splitData[4].indexOf(':') + 1), splitData[4].length()));
    OscBVolume[i] = float(splitData[5].substring((splitData[5].indexOf(':') + 1), splitData[5].length()));
    OscBDetune[i] = float(splitData[6].substring((splitData[6].indexOf(':') + 1), splitData[6].length()));

    NoiseVolume[i] = float(splitData[7].substring((splitData[7].indexOf(':') + 1), splitData[7].length()));

    LFOOnOff[i] = int(splitData[8].substring((splitData[8].indexOf(':') + 1), splitData[8].length()));
    LFORate[i] = float(splitData[9].substring((splitData[9].indexOf(':') + 1), splitData[9].length()));
    LFOAmount[i] = float(splitData[10].substring((splitData[10].indexOf(':') + 1), splitData[10].length()));
    LFODest[i] = int(splitData[11].substring((splitData[11].indexOf(':') + 1), splitData[11].length()));

    FilterOnOff[i] = int(splitData[12].substring((splitData[12].indexOf(':') + 1), splitData[12].length()));
    FilterQ[i] = float(splitData[13].substring((splitData[13].indexOf(':') + 1), splitData[13].length()));
    FilterCutoff[i] = float(splitData[14].substring((splitData[14].indexOf(':') + 1), splitData[14].length()));

    TriggerDest[i][0] = int(splitData[15].substring((splitData[15].indexOf(':') + 1), splitData[15].length()));
    TriggerDest[i][1] = int(splitData[16].substring((splitData[16].indexOf(':') + 1), splitData[16].length()));
    TriggerDest[i][2] = int(splitData[17].substring((splitData[17].indexOf(':') + 1), splitData[17].length()));    
    TriggerDest[i][3] = int(splitData[18].substring((splitData[18].indexOf(':') + 1), splitData[18].length()));

    AmpAttack[i] = int(splitData[19].substring((splitData[19].indexOf(':') + 1), splitData[19].length()));
    AmpRelease[i] = int(splitData[20].substring((splitData[20].indexOf(':') + 1), splitData[20].length()));
  }
  println(LFOOnOff);
}

// Event listener for all controller events
void controlEvent(ControlEvent e) { 
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
    mgPort.write(e.getName() + "," + value + "\n");
  }
  
  if (e.isFrom(comPortList)) { // if dropdown list has been clicked
    if (isDeviceConnected) { // clear and stop existing serial port if device is connected
      mgPort.clear();
      mgPort.stop();
    }
    isDeviceConnected = true;
    portName = Serial.list()[int(e.getValue())]; // Connect to device
    mgPort = new Serial(this, portName, 115200);
    mgPort.write("CONNECT\n");
    appState = "LOADING"; // go to loading state on connect
  } 

  if (e.isFrom(closeButton)) {
    if (isDeviceConnected) {
      mgPort.write("DISCONNECT\n");
    }
    exit();
  }

  if (e.isFrom(saveButton)){
    mgPort.write("SAVE\n");
    appState = "LOADING";
  }

  if (e.isFrom(bankNumberbox)) {
    bankIndex = int(e.getValue());
    //println(bankIndex);
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
  }
}

void keyPressed() {
  if (key == ' ' && keyBounce) {
    mgPort.write("playPause,1\n");
  }
  keyBounce = false;
}

void keyReleased() {
  if (key == ' ' && isDeviceConnected) {
    mgPort.write("playPause,0\n"); 
    keyBounce = true;
  }
}

void stop() {
  if (isDeviceConnected) {
    mgPort.write("DISCONNECT\n");
  }
}
