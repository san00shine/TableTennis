#include <TimerOne.h>
#include "MusicDefines.h"
#include "LCDDefines.h"


const int pinBuzzer = A1;      // buzzer pin
const int pinButtons = A0;     // input pin for the buttons
const int pinsDisplayDigitParts[] = {2, 3, 4, 5, 6, 7, 8};
const int pinsDisplayDigits[] = {13, 12, 11, 10};
const int pinDisplayDecimalDot = 9;
const int pinsDisplayDigitPartsCount = sizeof(pinsDisplayDigitParts) / sizeof(pinsDisplayDigitParts[0]);
const int pinsDisplayDigitsCount = sizeof(pinsDisplayDigits) / sizeof(pinsDisplayDigits[0]);

// takes a character and returns the parts of a 7-LED digit that need to be on
byte charToShape(char letter)
{
  if ((letter == 0) or (letter == ' ') or (letter == '\t')) return 0;
  if (letter < 'A') return digitShapes[letter - '0']; // in the ASCII table, digits are lower than letters, and uppercase letters are below lowercase
  if (((letter >= 'a') && (letter <= 'z')) ||
      ((letter >= 'A') && (letter <= 'Z')))
  {
    letter = letter | 32; // turn to lowercase - flip bit 5 to 1
    return letterShapes[letter - 'a'];
  }
  return 1<<6 | 0<<5 | 0<<4 | 0<<3 | 0<<2 | 0<<1 | 0<<0 ; // use '-' for 'unavailable' characters
}

// display 'letter' on the currently active digits on the LCD display
void displayChar(char letter)
{
  byte activePins = charToShape(letter);
  int currentPiece = 0;
  byte mask = 1;
  while (currentPiece < pinsDisplayDigitPartsCount)
  {
    
    digitalWrite(pinsDisplayDigitParts[currentPiece], (activePins & mask) ? HIGH : LOW);
    mask = mask << 1;
    currentPiece ++;
  }
}

// send a mask of active/inactive digits for the LCD Display - bit 0 for digit 0, bit 1 for digit 1...
void setActiveDigits(byte digits)
{
  int currentDigit = 0;
  byte mask = 1;
  while (currentDigit < pinsDisplayDigitsCount)
  { 
    //turn pin to LOW if we want to write to this digit, else set to HIGH
    digitalWrite(pinsDisplayDigits[currentDigit], (digits & mask) ? LOW : HIGH); 
    mask = mask << 1;
    currentDigit ++;
  }
}

enum eDisplayType
{
  DT_OFF = 0,
  DT_STATIC,
  DT_SCROLL,
  DT_ANIMATION,

  DT_MAX_STATES
};

class Display
{
  static const byte MAX_TEXT_LENGTH = 32;
  eDisplayType state;
  byte score1;
  byte score2;
  char scrollText[MAX_TEXT_LENGTH];
   
};

class Song
{
  // change this to make the song slower or faster
  int tempo;

  // int array: notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!  
  int const *melody;

  int notes;
  int wholenote;

  bool stopPlay;

public:
  Song(int _tempo, const int* _melody, int _notes):
    tempo(_tempo),
    melody(_melody),
    notes(_notes),
    stopPlay(false)
  {
    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / tempo;
  }

  void stopSong()
  {
    stopPlay = true;
  }

  void play()
  {    
    int divider = 0, noteDuration = 0;
    stopPlay = false;
    
    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
    {  
      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) 
      {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) 
      {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
  
      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(pinBuzzer, melody[thisNote], noteDuration * 0.95);
  
      // Wait for the specified duration before playing the next note.
      delay(noteDuration);
  
      // stop the waveform generation before the next note.
      noTone(pinBuzzer);

      if(stopPlay)
        break;
    }    
  }
};


Song keyboardCat(160, melody_keyBoardCat, NOTES(melody_keyBoardCat));
Song supermariobros(200, melody_supermariobros, NOTES(melody_supermariobros));
Song harrypotter(144, melody_harrypotter, NOTES(melody_harrypotter));
Song *songs[] = {&keyboardCat, &supermariobros, &harrypotter};
int songsCount = sizeof(songs) / sizeof(songs[0]);
int currentSong = -1;

void StopSongs()
{
  for (int i = 0; i < songsCount; i++)
    songs[i]->stopSong();
}

int m = 0;
int stringPosition = -1;
const char *displayString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// called by the timer
void Interrupt_CheckButtons()
{
  int sensorValue = analogRead(pinButtons);

  if ((sensorValue > 100) && (sensorValue < 300))
  {
    if (currentSong != 0)
    {
      currentSong = 0;
      StopSongs();
    }
  }
  else if ((sensorValue > 300) && (sensorValue < 500))
  {
    if (currentSong != 2)
    {
      currentSong = 2;
      StopSongs();
    }
  }  
  else if ((sensorValue > 1000))
  {
    if (currentSong != -1)
    {
      currentSong = -1;
      StopSongs();
    }
  }
  else
  {
    //nothing
  } 

  m++;
  if (m > 40)
  {
    stringPosition ++;
    if (displayString[stringPosition] == '\0')
    {
      stringPosition = 0;
    }
    setActiveDigits(1 << (stringPosition % 4));
    displayChar(displayString[stringPosition]);
    m = 0;
  }
 
}

void setup() 
{ 
  for (byte i = 0; i < pinsDisplayDigitPartsCount; i++)
    pinMode(pinsDisplayDigitParts[i], OUTPUT);
  for (byte i = 0; i < pinsDisplayDigitsCount; i++)
    pinMode(pinsDisplayDigits[i], OUTPUT); 
  
  Timer1.initialize(25000); 
  Timer1.attachInterrupt(Interrupt_CheckButtons);     

  //Serial.begin(9600);
}

enum eTTStates
{
  TTS_INTRO = 0, //short intro animation, no input
  TTS_WAIT_SERVE_SELECTION, //scroll text, wait for players to select who starts
  TTS_GAME_RUNNING,
  TTS_SET_OVER, //short animation between sets
  TTS_GAME_OVER, //display winner

  TTS_MAX_STATES
};

eTTStates currentState = TTS_INTRO;


void loop() 
{
  
  while(true)
  {
    if (currentSong > -1)
      songs[currentSong]->play();

    delay(1);    
      
  }
}
