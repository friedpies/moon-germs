// conversion to map IR sensor reading to a value between 0 and 1
//
float mapIRtoFloat(int irReading) {
  float conversion = (3.11 * exp(-0.00538 * float(irReading))) - 1;
  if (conversion > 1) {
    conversion = 1;
  }
  if (conversion < -1) {
    conversion = -1;
  }
  return conversion;
}


