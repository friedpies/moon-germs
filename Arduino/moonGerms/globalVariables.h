Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button4 = Bounce(BUTTON_1, 15);
Bounce button3 = Bounce(BUTTON_2, 15);
Bounce button2 = Bounce(BUTTON_3, 15);
Bounce button1 = Bounce(BUTTON_4, 15);

// Arrays to store saved presets
const int numberOfBanks = 4;
int bank; // current bank
int Bank[numberOfBanks];

float MasterVolume[numberOfBanks] = {0.5, 0.5, 0.5, 0.5};

int OscAWaveform[numberOfBanks] = {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_TRIANGLE};
float OscAVolume[numberOfBanks] = {.5, .5, .5, .5};

int OscBWaveform[numberOfBanks] = {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_TRIANGLE};
float OscBVolume[numberOfBanks] = {.5, .5, .5, .5};
float OscBDetune[numberOfBanks] = {1.0, 1.0, 1.0, 1.0};

float NoiseVolume[numberOfBanks] = {0, 0, 0, 0}; // will need to remove this

boolean LFOOnOff[numberOfBanks] = {false, false, false, false};
float LFORate[numberOfBanks] = {0, 0, 0, 0};
float LFOAmount[numberOfBanks] = {0, 0, 0, 0};
int LFODest[numberOfBanks]; // this is not needed

boolean FilterOnOff[numberOfBanks] = {false, false, false, false}; // if LFO is on, filter must be on
float FilterQ[numberOfBanks] {1.0, 1.0, 1.0, 1.0};
float FilterCutoff[numberOfBanks] = {100, 100, 100, 100};

int TriggerDest[numberOfBanks][4] = { // all banks allow for trigger to control Detune on start
  {1, 0, 0, 0}, // Trigger Destination is as follow {OSC B DETUNE, FILTER CUTOFF, LFO RATE, LFO AMOUNT};
  {1, 1, 0, 0},
  {1, 0, 0, 0},
  {1, 0, 0, 0}
};
int AmpAttack[numberOfBanks] = {50, 50, 50, 50};
int AmpRelease[numberOfBanks] = {100, 100, 100, 100};

int AnimationLength[numberOfBanks] = {sawWaveBMPSize, squareWaveBMPSize, sawWaveReverseBMPSize, triangleWaveBMPSize};
int DisplayColor[numberOfBanks] = {LED_YELLOW, LED_GREEN, LED_RED, LED_GREEN};
uint8_t CurrentAnimation[numberOfBanks][22][8] = {sawWaveBMP[22][8], squareWaveBMP[22][8], sawWaveReverseBMP[22][8], triangleWaveBMP[22][8]};
int CurrentAnimationSize[numberOfBanks] = { sawWaveBMPSize, squareWaveBMPSize, sawWaveReverseBMPSize, triangleWaveBMPSize};


// 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
uint8_t currentAnimation[22][8];// 22 frame array to hold animations
int animationLength = sawWaveBMPSize; // computes number of frames of selected animation
int currentFrame = 0;
int frameRate = 50; // milliseconds between each frame
int lastMillis = 0; //time elapsed since previous frame
int displayColor = LED_RED;
boolean playAnimation = false;

int triggerRead;
int previousTriggerRead;

const int numReadings = 300; // Number of samples to average for IR sensor reading
int infraredReadings[numReadings]; // Array containing samples of IR readings
int readIndex = 0;
float readingAverage;
float mappedAverage;

int octaveCounter = 2;
float centerFreq = noteA[octaveCounter]; // set global frequency to A3
float globalFreq = centerFreq; // actual frequency being generated, dependent on IR sensor (bendFactor) and octave
float bendFactor;
float globalGain;

float detuneTrig = 1.0; // dynamic variables, these change with trigger
float cutoffTrig = 1.0; // filter cutoff multiplier
float rateTrig = 1.0; // LFO rate multiplier
float amountTrig = 1.0; // LFO amount multiplier

String incomingData = "";
String parameter = "";
String value = "";

boolean isConnected = false;
