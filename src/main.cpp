#include <Arduino.h>
#include "pitches.h"
#define SONG_COUNT (sizeof(songs)/sizeof(Song))
#define BUZZER_PIN 9
#define POT A7
#define btn1 2
#define btn2 3
#define btn3 4
int stopFlag = 1; // start with stopped
int song = 0;

struct Song {
  const int* melody;
  const int* durations;
  int length;
};

const int melody1[] = {
  NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_G5,
  NOTE_F5, NOTE_DS5, NOTE_DS5, NOTE_F5, NOTE_D5,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_C6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_G5,
  NOTE_F5, NOTE_DS5, NOTE_DS5, NOTE_F5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_C6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_AS5, NOTE_AS5, 
  //NOTE_AS5, NOTE_A5, NOTE_GS5, NOTE_G5,
};

const int durations1[] = {  
  4,2,2,4,2,2,
  2,2,2,4,
  2,4,2,4,1,
  4,2,4,2,4,
  1,4,2,4,2,
  4,1,4,2,
  2,4,2,2,2,2,2,4,
  2,4,2,4,1,4,2,4,2,4,1,
  4,2,4,2,4,2,
  //6,6,6,6,6,6,6,6,6,6,6,6,
};

const int melody0[] = {
  NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_B4, NOTE_E5, NOTE_DS5, 
  NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5,
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_E5, NOTE_DS5,
  NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_B4, NOTE_E5, NOTE_DS5,
  NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5,
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_E5, NOTE_DS5,
  //
  NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_CS5, NOTE_DS5, 
  NOTE_CS5, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_DS5, NOTE_CS5, NOTE_B4,
  NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_DS5, NOTE_CS5, NOTE_DS5, NOTE_FS5, NOTE_B5,
  NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_GS5,
};

const int durations0[] = {
  2,2,1,2,2,1,
  8,8,8,8,8,8,8,8,8,8,4,
  4,8,8,8,4,4,4,4,2,2,
  2,2,1,2,2,1,
  8,8,8,8,8,8,8,8,8,8,4,
  4,8,8,8,4,4,4,4,2,2,
  //
  8,8,4,4,8,4,3,4,8,4,
  8,8,8,8,8,4,4,8,2,
  8,8,4,4,8,4,8,4,4,2,
  4,6,8,2,

};

const int melody2[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  
  NOTE_A4, NOTE_A4,
  //Repeat of first part
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  //End of Repeat
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,
  
  NOTE_E5, REST, REST, NOTE_F5, REST, REST,
  NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
  NOTE_D5, REST, REST, NOTE_C5, REST, REST,
  NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4
};

const int durations2[] = {
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  
  4, 8,
  //Repeat of First Part
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  //End of Repeat
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2,
  
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 8, 2
};

const int melody3[] = {
  NOTE_B4, NOTE_E4, NOTE_G4, REST, NOTE_E4, REST,
  NOTE_DS4, NOTE_DS4, NOTE_DS4, NOTE_DS4, REST,

  NOTE_G4, REST,
  NOTE_G4, NOTE_G4, REST,
  NOTE_G4, REST,
  NOTE_G4, NOTE_D4, NOTE_G4, REST, NOTE_G4, REST, 

  NOTE_C4, REST, NOTE_D4, REST, NOTE_E4, REST, NOTE_G4, REST,
  NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_E4, REST, NOTE_E4, REST, NOTE_E4, REST,
  REST
};

const int durations3[] = {
  4, 6, 6, 8, 6, 6,
  4, 6, 4, 3, 4,

  6, 8,
  6, 6, 8,
  6, 8,
  4, 6, 4, 16, 2, 8,
  
  4, 6, 4, 6, 4, 6, 4, 8,
  6, 6, 6,
  6, 3, 6, 3, 6, 3,
  1
};

const Song songs[] = {
  //Unravel from Tokyo Ghoul
  {melody0, durations0, sizeof(melody0) / sizeof(int)},
  //test
  {melody1, durations1, sizeof(melody1) / sizeof(int)},
  //Pirates of the Caribbean theme
  {melody2, durations2, sizeof(melody2) / sizeof(int)},
  //test
  {melody3, durations3, sizeof(melody3) / sizeof(int)}
};

void waitRelease(int pin){
  while(digitalRead(pin)==HIGH);
  delay(50); // debounce
}

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(POT, INPUT);
}

void check(){
  if (digitalRead(btn1)==HIGH && song>0){
    song--;
    waitRelease(btn1);
  }
  if (digitalRead(btn3)==HIGH && song<SONG_COUNT-1){
    song++;
    waitRelease(btn3);
  }
  if (digitalRead(btn2)==HIGH){
    stopFlag = !stopFlag;
    waitRelease(btn2);
  }
}

void loop() {
  check();
  if(stopFlag) return;
  int size = songs[song].length;
  for(int note=0; note<size; note++){
    check();
    if(stopFlag) break; // stop during song
    int duration = 1000 / songs[song].durations[note];
    tone(BUZZER_PIN, songs[song].melody[note], duration);
    delay(duration * 1.3);
    noTone(BUZZER_PIN);
  }
  stopFlag = 1; // stop after song
}