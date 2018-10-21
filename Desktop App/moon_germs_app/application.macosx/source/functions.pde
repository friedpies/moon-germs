
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
  } else if (frameCount <= (30 * time3)) {
    pixelateImage(2, splashScreen);
  }
}

// Event listener for all controller events
void controlEvent(ControlEvent e) { 
  if (isDeviceConnected) {
    mgPort.write(e.getName() + "," + e.getValue() + "\n");
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
    println("Connected to " + mgPort);
  }
}

void keyPressed() {
  if (isDeviceConnected && keyBounce) {
    switch (key) {
    case 'z':
      mgPort.write("playPause,c1\n");
      break;
    case 'x':
      mgPort.write("playPause,d1\n");
      break;
    case 'c':
      mgPort.write("playPause,e1\n");
      break;
    case 'v':
      mgPort.write("playPause,f1\n");
      break;
    case 'b':
      mgPort.write("playPause,g1\n");
      break;
    case 'n':
      mgPort.write("playPause,a1\n");
      break;
    case 'm':
      mgPort.write("playPause,b1\n");
      break;
    case ',':
      mgPort.write("playPause,c2\n");
      break;
    case ' ':
      mgPort.write("playPause,1\n");
    }
    keyBounce = false;
  }
}

void keyReleased() {
  if (key == ' ' && isDeviceConnected) {
    mgPort.write("playPause,0\n"); 
    keyBounce = true;
  }
}