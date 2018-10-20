
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button4 = Bounce(BUTTON_1, 15);
Bounce button3 = Bounce(BUTTON_2, 15);
Bounce button2 = Bounce(BUTTON_3, 15);
Bounce button1 = Bounce(BUTTON_4, 15);

// Arrays to store saved presets
const int numberOfBanks = 4;
int bankIndex = 0;
int Bank[numberOfBanks];

float MasterVolume[numberOfBanks] = {0.25, 0.25, 0.25, 0.25};

int OscAWaveform[numberOfBanks] = {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_TRIANGLE};
float OscAVolume[numberOfBanks] = {.5, .5, .5, .5};

int OscBWaveform[numberOfBanks] = {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_TRIANGLE};
float OscBVolume[numberOfBanks] = {.5, .5, .5, .5};
float OscBDetune[numberOfBanks] = {1.0, 1.0, 1.0, 1.0};

float NoiseVolume[numberOfBanks] = {0, 0, 0, 0};

boolean LFOOnOff[numberOfBanks] = {false, false, false, false};
float LFORate[numberOfBanks] = {0, 0, 0, 0};
float LFOAmount[numberOfBanks] = {0, 0, 0, 0};
int LFODest[numberOfBanks];

boolean FilterOnOff[numberOfBanks] = {false, false, false, false};
int FilterQ[numberOfBanks] {.707, .707, .707, .707};
float FilterCutoff[numberOfBanks] = {10000, 10000, 10000, 10000};

int TriggerDest[numberOfBanks];
int AmpAttack[numberOfBanks] = {0, 0, 0, 0};
int AmpRelease[numberOfBanks] = {0, 0, 0, 0};

int AnimationLength[numberOfBanks] = {sawWaveBMPSize, squareWaveBMPSize, sawWaveReverseBMPSize, triangleWaveBMPSize};
//int DisplayColor[numberOfBanks] = {LED_YELLOW, LED_GREEN, LED_RED, LED_GREEN};
//uint8_t CurrentAnimation[numberOfBanks][22][8] = {sawWaveBMP, squareWaveBMP, sawWaveReverseBMP, triangleWaveBMP};

////////////////////////////////////////////////////
/// shared variables with Desktop App, temporary variables
boolean pressPlay = false;
int bank;

float masterVolume = 1.0;

float oscAVolume = 0.75;
int oscAWaveform = WAVEFORM_SAWTOOTH;

float oscBVolume = 0.75;
int oscBWaveform = WAVEFORM_SAWTOOTH;
float oscBDetune = 1.0;

float noiseVolume = 0.25;

boolean lfoOnOff;
float lfoRate;
float lfoAmount;
int lfoDest;

boolean filterOnOff;
float filterQ;
float filterCutoff;

int triggerDest;
int ampAttack;
int ampRelease;



// 0:Sine, 1:Sawtooth, 2:Square, 3:Triangle, 6:Reverse Saw
int waveformType = WAVEFORM_SAWTOOTH; // default waveform on both oscillators
uint8_t currentAnimation[22][8];// 20 frame array to hold animations
int animationLength = sawWaveBMPSize; // computes number of frames of selected animation
int currentFrame = 0;
int frameRate = 50; // milliseconds between each frame
int lastMillis = 0; //time elapsed since previous frame
int displayColor = LED_RED;
boolean playAnimation = false;

int triggerRead;

const int numReadings = 300; // Number of samples to average for IR sensor reading
int infraredReadings[numReadings]; // Array containing samples of IR readings
int readIndex = 0;
float readingAverage;
float mappedAverage;

int octaveCounter = 4;
float centerFreq = noteA[octaveCounter]; // set global frequency to A3
float globalFreq = centerFreq; // actual frequency being generated, dependent on IR sensor (bendFactor) and octave
float bendFactor;
float globalGain;
float detune = 1.0;

String incomingData = "";
String parameter = "";
String value = "";

enum states deviceState = STANDALONE_STATE;
