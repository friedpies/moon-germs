// Moon Germs Desktop App
// V0.1 Processing Code

// Hardware and software files can be found at: https://github.com/friedpies/moon-germs
// Project Details: https://hackaday.io/project/161208-moon-germs
// License: MIT

import processing.serial.*;

Serial mgPort;
String incomingData;

void settings() {
}

void setup() {
  fullScreen();
  background(0);
  String[] ports = Serial.list();
  println(ports);
}

void draw() {
}
