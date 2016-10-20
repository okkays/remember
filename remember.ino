#define DEBUG 0

#define c1 65
#define d1 73
#define e1 82
#define f1 87
#define g1 98
#define a1 110
#define b1 123

#define c2 131
#define d2 147
#define e2 165
#define f2 175
#define g2 196
#define a2 220
#define b2 246

#define c3 261
#define d3 294
#define e3 329
#define f3 349
#define g3 392
#define a3 440
#define b3 493

#define c4 523
#define d4 587
#define e4 659
#define f4 698
#define g4 783
#define a4 880
#define b4 988

#define PLAY 0
#define HOLD 1
#define REST 2

#define FAN_ON 53

#define buzzerPin 9
#define ledPin 13
#define fanPin 6

float bpm = 180.0;
float qu = 60.0 / bpm;
float ei = qu / 2.0;
float ha = 2.0 * qu;
float wh = 4.0 * qu;
float si = qu / 4.0;
float dq = 1.5 * qu;
float de = 1.5 * ei;
float dh = 1.5 * ha;
float ds = 1.5 * si;

int notes[] =
{
  // 372
  a3, b3, c4, d4, e4, f4, g4, a4, b4, a4, g4, f4, g4, f4, e4, d4, c4, b3, c4, b3, a3, // 21
  // 374
  g3, g3, g3, g3, a3, b3, a3, c4, a3, f3, g3, // 11
  // 377 + 1
  f4, e4, f4, g4, a4, f4, g4, a4, b4, a4, g4, f4, b4, a4, g4, f4, b4, a4, g4, f4, // 20
  // 379 Allegro vivace.
  e4, b3, b3, e4, f4, g4, f4, e4, f4, g4, e4, e4, // 12
  // 381
  b3, b3, e4, f4, g4, f4, e4, f4, g4, e4, e4, // 11
  // 383
  c4, c4, f4, g4, f4, c4, a3, c4, f4, c4, a3, c4, f4, // 13
  // 385
  b3, b3, e4, f4, e4, b3, g3, b3, e4, b3, g3, b3, e4, // 13
  // 387 marcato
  b1, c2, c2, b1, g1, e1, e2, d2, c2, b1, g1, e1 // 12
};
float holds[] =
{
  // 372
  si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si,
  // 374
  ei, ei, ei, ei, qu * 2.0, qu, qu, dq, ei, qu, qu,
  // 377 + 1
  si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si,
  // 379 Allegro vivace.
  ha, si, si, ei, ei, ei, ei, ei, ei, qu, qu, ha,
  // 381
  si, si, ei, ei, ei, ei, ei, ei, qu, qu, ha,
  // 383
  si, si, ei, ei, ei, ei, ei, ei, ei, ei, ei, ei, ha,
  // 385
  si, si, ei, ei, ei, ei, ei, ei, ei, ei, ei, ei, ha,
  // 387 marcato
  wh, ha, ha, ha, qu, wh, wh, ha, ha, ha, qu, wh
};
float rests[] =
{
  // 372
  si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si,
  // 374
  ei, ei, ei, ei, qu * 2.0, qu, qu, dq, ei, qu, qu,
  // 377 + 1
  si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si, si,
  // 379 Allegro vivace.
  ha, si, si, ei, ei, ei, ei, ei, ei, qu, qu, ha,
  // 381
  si, si, ei, ei, ei, ei, ei, ei, qu, qu, ha,
  // 383
  si, si, ei, ei, ei, ei, ei, ei, ei, ei, ei, ei, ha,
  // 385
  si, si, ei, ei, ei, ei, ei, ei, ei, ei, ei, ei, ha,
  // 387 marcato
  ha, qu, qu, qu, ei, ha, ha, qu, qu, qu, ei, wh
};

int index = 0;
int stage = PLAY;

void setup() {
  delay(1000);
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  if (DEBUG) {
    Serial.begin(9600);
  }
}

void startFan() {
  analogWrite(fanPin, 255);
}

void stopFan() {
  analogWrite(fanPin, 0);
}

void prepareNext() {
  stage++;
  if (stage == 3) {
    stage = 0;
    index++;
    if (index == FAN_ON) {
      startFan();
    }
    if (index >= (sizeof(notes) / sizeof(int))) {
      index = 0;
      stopFan();
      delay(2000);
    }
    Serial.println("On index: ");
    Serial.print(index, DEC);
  }
}

void doStage() {
  switch (stage) {
    case PLAY:
      if (DEBUG) {
        Serial.print("PLAY: ");
        Serial.println(notes[index], DEC);
      }
      tone(buzzerPin, notes[index]);
      digitalWrite(ledPin, HIGH);
      break;
    case HOLD:
      if (DEBUG) {
        Serial.print("HOLD: ");
        Serial.println(holds[index], DEC);
      }
      delay(holds[index] * 1000.0);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      break;
    case REST:
      if (DEBUG) {
        Serial.print("REST: ");
        Serial.println(rests[index], DEC);
      }
      delay(rests[index] * 500.0);
      break;
  }
}

void loop() {
  doStage();
  prepareNext();
}
