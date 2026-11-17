// ---------------- Pins (must come BEFORE robot.h) ----------------
#define ENA 11
#define IN1 10
#define IN2 8
#define ENB 6
#define IN3 9
#define IN4 5

#define LSensor A0
#define RSensor A1
#define FSensor A2
#define MSensor A5

#define BZ_A 7
#define BZ_B 12

#include "robot.h"

int F[3] = {A0,A1,A2};  // left, right, front

// ---------------- Sensor data structure ----------------
typedef struct {
  int rawL, rawF, rawR, rawM;   
  int cmL, cmF, cmR;            
} SensorData;

void setup() {
  Serial.begin(9600);
  pinMode(BZ_A, OUTPUT);
  pinMode(BZ_B, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LSensor, INPUT);
  pinMode(RSensor, INPUT);
  pinMode(FSensor, INPUT);
  pinMode(MSensor, INPUT);

  // view();

  startSound();

  delay(1000);
}

void loop() {
  if (Read_Eye(LSensor) <= 5) {
    delay(1000);
    if (Read_Eye(LSensor) <= 5) {
      beep(1, 100); delay(1000);
      while (analogRead(MSensor) > 450) Track_wall_L();
      MotorControl(0, 0); while (1);
    }
  }

  if (Read_Eye(RSensor) <= 5) {
    delay(1000);
    if (Read_Eye(RSensor) <= 5) {
      beep(2, 100); delay(1000);
      while (analogRead(MSensor) > 450) Track_wall_R();
      MotorControl(0, 0); while (1);
    }
  }
}

void readSensors(SensorData *s) {
  s->rawL = analogRead(LSensor);
  s->rawF = analogRead(FSensor);
  s->rawR = analogRead(RSensor);
  s->rawM = analogRead(MSensor);

  s->cmL = Read_Eye(LSensor);
  s->cmF = Read_Eye(FSensor);
  s->cmR = Read_Eye(RSensor);
}

void view() {
  SensorData data;
  SensorData *p = &data;

  while (true) {
    readSensors(p);

    Serial.print("\tL    : "); Serial.print(p->rawL); Serial.print("\t");
    Serial.print("\tF    : "); Serial.print(p->rawF); Serial.print("\t");
    Serial.print("\tR    : "); Serial.print(p->rawR); Serial.print("\t");
    Serial.print("\tM    : "); Serial.println(p->rawM);
    Serial.print("\tL-CM : "); Serial.print(p->cmL); Serial.print("\t");
    Serial.print("\tF-CM : "); Serial.print(p->cmF); Serial.print("\t");
    Serial.print("\tR-CM : "); Serial.println(p->cmR);
    Serial.println("\t----------------------------------------------------------------------------------");
    delay(1000);
  }
}

void startSound() {
  sweep(300, 2000, 450);
  delay(120);
  sound(1568, 60); delay(60);
  sound(1568, 60); delay(150);
  sound(1047, 110); delay(30);
  sound(1568, 110); delay(30);
  vibrato(2093, 450);
}

void beep(int n, int ms) {
  for (int i = 0; i < n; i++) {
    sound(2000, ms); delay(ms);
  }
}

void sound(int freq, int ms) {
  if (freq == 0) { delay(ms); return; }
  freq = freq * 1.3;
  long halfPeriod = 500000L / freq;
  long cycles = (long)freq * ms / 1000;
  for (long i = 0; i < cycles; i++) {
    digitalWrite(BZ_A, HIGH); digitalWrite(BZ_B, LOW);
    delayMicroseconds(halfPeriod);
    digitalWrite(BZ_A, LOW);  digitalWrite(BZ_B, HIGH);
    delayMicroseconds(halfPeriod);
  }
  digitalWrite(BZ_A, LOW); digitalWrite(BZ_B, LOW);
}

void sweep(int freq1, int freq2, int ms) {
  int steps = ms / 10;
  for (int i = 0; i <= steps; i++) {
    sound(freq1 + (long)(freq2 - freq1) * i / steps, 10);
  }
}

void vibrato(int freq, int ms) {
  for (int t = 0; t < ms; t += 40) {
    sound(freq, 20);
    sound(freq - 80, 20);
  }
}
