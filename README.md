## Moon Germs
#### A hand-held, battery powered digital synthesizer based on the Teensy 3.2 and Audio Shield by www.pjrc.com
![](https://github.com/friedpies/moon-germs/blob/master/Photos/device_top.jpg)
![](https://github.com/friedpies/moon-germs/blob/master/Photos/parts_top.jpg)
### About the Device
A fun, pocket-sized synthesizer that uses an IR proximity sensor to modulate frequency. Using a combination of buttons and triggers, the device can produce several different waveforms and effects. An 8x8 LED matrix shows useful and colorful information while in use. Currently finishing up Rev 1.0

I wanted to explore digital synthesis using the Teensy Audio shield and experiment with a unique way of interacting with a synthesizer with minimal buttons/knobs, all while designing a device with an interesting and retro form factor. Although I'm a lifelong musician, I never really explored synthesis before and thought this would be a great way to dive in. This has been an awesome learning experience and has gotten me hooked! I'm excited to keep this up.

--------
### Usage
The Moon Germs' synthesis engine consists of  2 oscillators and a pink noise generator. Pressing down button 1 activates the oscillators while their frequency is determined by the IR sensor. Button 2 cycles through various waveforms. Buttons 3 & 4 shift octaves up & down respectively. The spring loaded trigger applies a detune to oscillator 2.

![Synth](https://github.com/friedpies/moon-germs/blob/master/Photos/synthengine.png)
--------
### Demo
[Demo 1](https://youtu.be/qyO1_fC_Kus)

[Demo 2](https://youtu.be/aUcpQy3lOxo)

--------
### BOM and Build Instructions
Full BOM and assembly instructions found [here](https://github.com/friedpies/moon-germs/blob/master/BUILD_INSTRUCTIONS.md)

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

![](https://github.com/friedpies/moon-germs/blob/master/Photos/MOON_GERMS_DRAWING.png)

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
