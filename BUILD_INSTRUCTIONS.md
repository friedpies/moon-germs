### Moon Germs Pocket Synthesizer Build Instructions

#### Bill of Materials

***Off the Shelf Electronics:***
- 1x [Teensy 3.2 Development Board, no headers](https://www.pjrc.com/store/teensy32.html) $19.80
- 1x [Teensy Audio Adapter](https://www.pjrc.com/store/teensy3_audio.html) $14.25
- 1x [Adafruit PowerBoost 1000](https://www.adafruit.com/product/2465) $19.95
- 1x [Adafruit Bicolor LED Square Matrix with I2C Backpack](https://www.adafruit.com/product/902) $15.95
- 1x [2000 mAh rechargable LiPo Battery](https://www.digikey.com/product-detail/en/adafruit-industries-llc/2011/1528-1857-ND/6612469) $12.50
- 4x [Cherry Switches](https://www.sparkfun.com/products/13834) $3.80
- 1x [Sharp IR Sensor GP2Y0A41SK0F](https://www.sparkfun.com/products/12728) $13.95
- 1x [Bourns Linear Potentiometer PTA1543-2010CIB103](https://www.digikey.com/product-detail/en/bourns-inc/PTA1543-2010CIB103/PTA1543-2010CIB103-ND/3781161) $1.29
- 1x [SPST Toggle Switch](https://www.digikey.com/product-detail/en/cw-industries/GF-123-3011/CWI334-ND/4089772) $0.73

***Custom Electronics:***
- 1x [Moon Germs Teensy 3.2 Custom Breakout Board](https://github.com/friedpies/moon-germs/tree/master/Eagle)

***Off the Shelf Hardware:***
- 1x [Spring](https://www.mcmaster.com/9654k951) $7.00
- 12x [4mm M2 Plastic Screws](https://www.mcmaster.com/96817a840) $7.50
- 7x [8mm M2 Plastic Screws](https://www.mcmaster.com/96817a846) $8.12

***3D Printed / Laser Cut Parts:***
- [Enclosure, Bottom](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_ENCLOSURE_BOTTOM.stl)
- [Enclosure, Top](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_ENCLOSURE_TOP.stl)
- [Trigger](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_TRIGGER.stl)
- [Key Cap 1](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_KEY_1.stl)
- [Key Cap 2](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_KEY_2.stl)
- [Key Cap 3](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_KEY_3.stl)
- [Key Cap 4](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_KEY_4.stl)
- [Acrylic Display Cover](https://github.com/friedpies/moon-germs/blob/master/CAD/STLs/MOON_GERMS_DISPLAY_SHIELD.dxf)

### Gather Parts:
- Obtain all off-the-shelf hardware listed above
- 3D print all plastic components, 0.1mm to 0.15mm resolution for FDM printers with a 30% infill should be fine,
 0.03mm - 0.05mm for resin printers
- Cut display cover using 0.06" clear acrylic with a laser or die-cutter (optional)
- [Breakout board](https://github.com/friedpies/moon-germs/tree/master/Eagle) can be manufactured with PCB manufacturer of your choice (I use seeedstudio)

### Assemble/Solder Electronics:
- Solder Teensy 3.2 and audio shield using headers with Teensy ON TOP of audio shield, then solder Teensy+Audio shield to breakout board, clip headers with flush cutters:
![](https://github.com/friedpies/moon-germs/blob/master/Photos/teensy_breakout.jpg)
![](https://github.com/friedpies/moon-germs/blob/master/Photos/breakout_below.jpg)

- Assemble all electronics modules according to their documentation, DO NOT attach any headers. (Visit product links for assembly instructions)
- Solder all electronic components to breakout board according to the image below, refer to silkscreen for details:
![](https://github.com/friedpies/moon-germs/blob/master/Photos/electronics_assembly.jpg)

### Upload Firmware to Teensy 3.2
- Install Arduino IDE from [www.arduino.cc](https://www.arduino.cc/)
- Install Teensy loader software from [https://www.pjrc.com/teensy/loader.html](https://www.pjrc.com/teensy/loader.html)
- Download and open [Moon Germs firmware](https://github.com/friedpies/moon-germs/tree/master/Arduino/moonGerms) with Arduino IDE
- Install necessary Arduino libraries listed at the top of the moonGerms.ino file
- Connect Teensy board to computer with a micro-USB cable and upload moonGerms.ino, the 8x8 display should flash with a bootup Animation if the upload was successful

### Enclosure Assembly
- Assemble lower-half of enclosure according to the image below, use hot-glue to hold linear potentiometer in place:
![](https://github.com/friedpies/moon-germs/blob/master/Photos/lower_assembly_2.jpg)

- Assemble spring-trigger and insert into lower-half of enclosure using 2x 4mm M2 screws, ensure that linear potentiometer is properly captured by trigger cutout:
![](https://github.com/friedpies/moon-germs/blob/master/Photos/spring_trigger.jpg)

- Assemble upper-half of enclosure according to the image below:
![](https://github.com/friedpies/moon-germs/blob/master/Photos/upper_assembly.jpg)

### Test device
- Power on the device by flipping the on-off switch located on the bottom right side of the device, the display should play a bootup animation and pressing down button 1 should display a waveform. Plug in a pair of headphones to ensure the device is generating sound and play with the IR and trigger. If there are any issues, check connections!

### Final assembly!
- Carefully assemble the two halves of the enclosure, ensuring that wires are not caught or snagged during assembly. Use 7x 8mm M2 plastic screws to hold enclosure together.
![](https://github.com/friedpies/moon-germs/blob/master/Photos/device_top.jpg)
