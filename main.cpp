#include <Arduino.h>
#include "pitches.h"
#define BUZZER_PIN 9
#define btn1 2
#define btn2 3
#define btn3 4

int melody0[] = {
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

const int durations = {
  0: {
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
  }
}

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
}

void loop() {
  int stop = 0;
  int song = 0;
  if (btn1 && song > 0)song--;
  if (btn3 && song < 10)song++;
  if (btn2 && stop == 0)stop = 1;
  else if (btn2 && stop == 1)stop = 0;
  if (stop!=1) {
  int size = sizeof(durations) / sizeof(int);
  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);
    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
}