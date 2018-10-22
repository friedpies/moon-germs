### Desktop App (alpha version)

#### About
- App was built by Kenneth Marut using [Processing 3](https://processing.org/). If you're interested in messing around with the code, Processing can be downloaded [here](https://processing.org/download/). Once downloaded, open "moon_germs_app.pde"
- This is still very much an alpha version. The basic functionality of the program works, but there are several bugs. Additionally, the "save" feature has not been implemented.
- For Mac .app file click [here](https://github.com/friedpies/moon-germs/tree/master/Desktop%20App/moon_germs_app/application.macosx), and .exe files for both Mac and Windows [32](https://github.com/friedpies/moon-germs/tree/master/Desktop%20App/moon_germs_app/application.windows32) & [64](https://github.com/friedpies/moon-germs/tree/master/Desktop%20App/moon_germs_app/application.windows64) bit


#### Usage
- Launch app on either windows or mac using the methods listed above
- Turn on Moon Germs device and wait until boot up screen is finished
- Connect device to computer using micro-USB cable
- Click "SELECT COM PORT" dropdown menu and select your device's port. The device will display an animation upon connecting

![](https://github.com/friedpies/moon-germs/blob/master/Photos/comport.gif)
- Data from the device will auto-load into the app
- Experiment with the sounds by adjusting the knobs and switches, pressing down the device buttons and using the trigger will allow you to hear your creation!
- Cycle through banks with button 2

![](https://github.com/friedpies/moon-germs/blob/master/Photos/app_device.gif)
- To disconnect, press the disconnect icon. Unplug the usb cable, your changes will be saved until the device is power cycled (this will be updated in a later revision)

![](https://github.com/friedpies/moon-germs/blob/master/Photos/disconnect.gif)

#### About the Synth Structure and Adjustable Parameters
- A block diagram of the signal flow can be seen here

![](https://github.com/friedpies/moon-germs/blob/master/Photos/block_diagram.png)
- When the filter is turned "ON", the filterBypassMixer turns off channel 1, and turns on channel 2
- In order to hear the effects of the LFO, the filter must also be turned on
- The "Trigger Func" parameter causes the trigger to attenuate the selected parameter(s): Oscillator 2 Detune, Filter Cutoff Frequency, LFO Rate, and LFO Amount.

#### Acknowledgments
- http://www.sojamo.de/libraries/controlP5 for writing a great GUI library, ControlP5
