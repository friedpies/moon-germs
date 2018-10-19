
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix(); // Initialize 8x8 Matrix

//Initial the 4 Cherry switches using Bounce library
Bounce button4 = Bounce(BUTTON_1, 15);
Bounce button3 = Bounce(BUTTON_2, 15);
Bounce button2 = Bounce(BUTTON_3, 15);
Bounce button1 = Bounce(BUTTON_4, 15);

// Arrays to store saved presets
const int numberOfBanks = 10;
int Bank[numberOfBanks];

float MasterVolume[numberOfBanks];

int OscAWaveform[numberOfBanks];
float OscAVolume[numberOfBanks];

int OscBWaveform[numberOfBanks];
float OscBVolume[numberOfBanks];
float OscBDetune[numberOfBanks];

float NoiseVolume[numberOfBanks];

boolean LFOOnOff[numberOfBanks];
float LFORate[numberOfBanks];
float LFOAmount[numberOfBanks];
int LFODest[numberOfBanks];

boolean FilterOnOff[numberOfBanks];
int FilterQ[numberOfBanks];
float FilterCutoff[numberOfBanks];

int TriggerDest[numberOfBanks];
int AmpAttack[numberOfBanks];
int AmpRelease[numberOfBanks];

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

int lfoOnOff;
float lfoRate;
float lfoAmount;
int lfoDest;

int filterOnOff;
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
