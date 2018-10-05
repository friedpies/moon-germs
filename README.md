## Moon Germs
#### A hand-held, battery powered digital synthesizer based on the Teensy 3.2 and Audio Shield by www.pjrc.com
![](https://github.com/friedpies/moon-germs/blob/master/Photos/MOON_GERMS_RENDER_BELOW.png)
### About the Device
A fun, pocket-sized synthesizer that uses IR proximity as its primary input. Using a combination of buttons and triggers, the device can produce several different waveforms and effects. An 8x8 LED matrix shows useful and colorful information while in use. Currently finishing up Rev 1.0

I wanted to explore digital synthesis using the Teensy Audio shield and experiment with a unique way of interacting with a synthesizer, all while designing a device with an interesting and retro form factor. Although I'm a lifelong musician, I never really explored synthesis. This has been an awesome learning experience and has gotten me hooked! I'm excited to keep this up.

--------
### Usage
The Moon Germs' synthesis engine consists of  2 oscillators and a pink noise generation. Pressing down button 1 activates the oscillators while their frequency is determined by the IR sensor. Button 2 cycles through various waveforms. Buttons 3 & 4 shift octaves up & down respectively. The spring loaded trigger applies a detune to oscillator 2.
![Synth](https://github.com/friedpies/moon-germs/blob/master/Photos/synthengine.png)

--------
### BOM
***Electronics:***
- 1x [Teensy 3.2 Development Board, no headers](https://www.pjrc.com/store/teensy32.html) $19.80
- 1x [Teensy Audio Adapter](https://www.pjrc.com/store/teensy3_audio.html) $14.25
- 1x [Adafruit PowerBoost 1000](https://www.adafruit.com/product/2465) $19.95
- 1x [Adafruit Bicolor LED Square Matrix with I2C Backpack](https://www.adafruit.com/product/902) $15.95
- 1x [2000 mAh rechargable LiPo Battery](https://www.digikey.com/product-detail/en/adafruit-industries-llc/2011/1528-1857-ND/6612469) $12.50
- 4x [Cherry Switches](https://www.sparkfun.com/products/13834) $3.80
- 1x [Sharp IR Sensor GP2Y0A41SK0F](https://www.sparkfun.com/products/12728) $13.95
- 1x [Bourns Linear Potentiometer PTA1543-2010CIB103](https://www.digikey.com/product-detail/en/bourns-inc/PTA1543-2010CIB103/PTA1543-2010CIB103-ND/3781161) $1.29
- 1x [SPST Toggle Switch](https://www.digikey.com/product-detail/en/cw-industries/GF-123-3011/CWI334-ND/4089772) $0.73
- 1x [Moon Germs Teensy 3.2 Custom Breakout Board](https://github.com/friedpies/moon-germs/tree/master/Eagle)

***Plastic:***
- Main Housing, A
- Main Housing, B
- Trigger
- Key Caps
- Acrylic Display Cover

***Off the Shelf Hardware:***
- 1x [Spring](https://www.mcmaster.com/9654k951) $7.00
- 12x [4mm M2 Plastic Screws](https://www.mcmaster.com/96817a840) $7.50
- 7x [8mm M2 Plastic Screws](https://www.mcmaster.com/96817a846) $8.12
--------
###  Electronics
- Schematic, Board, and CAM can be found [here](https://github.com/friedpies/moon-germs/tree/master/Eagle)
- PCB was manufactured using https://www.seeedstudio.com/fusion.html
--------
### Code
Arduino Code can be found [here](https://github.com/friedpies/moon-germs/tree/master/Arduino/moonGerms)

--------
### CAD + 3D Printing
STEP files of full assembly and STL files for 3D printing can be found [here](https://github.com/friedpies/moon-germs/tree/master/CAD)

--------
### Acknowledgments
- [PJRC](www.pjrc.com) for developing such a great audio shield and great tutorials, this thing is awesome!
- [Notes and Volts](www.notesandvolts.com) for such useful tutorials on how to use the Teensy Audio shield
- [LED Matrix Editor](https://xantorohara.github.io/led-matrix-editor/) A great GUI for creating 8x8 matrix animations.
- [Adafruit](www.adafruit.com) for their great electronics modules and Arduino libraries.
- Several [GrabCAD](www.grabcad.com) users for uploading and sharing their component models (shoutouts in /CAD folder)
--------
### Author & License
Author: Kenneth Marut (www.kennethmarut.com)
License: MIT
