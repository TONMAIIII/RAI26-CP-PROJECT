#include <math.h>

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

int lastErrorL = 0;
int lastErrorR = 0;

int Position = 0, errorL = 0, errorR = 0;
int PowerMotor = 0, LeftMotor = 0, RightMotor = 0;

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
      MotorControl(0, 0); while(1);
    }
  }

  if (Read_Eye(RSensor) <= 5) {
    delay(1000);
    if (Read_Eye(RSensor) <= 5) {
      beep(2, 100); delay(1000);
      while (analogRead(MSensor) > 450) Track_wall_R();
      MotorControl(0, 0); while(1);
    }
  }
}

void setMotor(int pwm, int pin1, int pin2, int speed) {
  speed = constrain(speed, -255, 255);
  digitalWrite(pin1, speed > 0 ? HIGH : LOW);
  digitalWrite(pin2, speed < 0 ? HIGH : LOW);
  analogWrite(pwm, abs(speed));
}

void MotorControl(int left, int right) {
  setMotor(ENA, IN1, IN2, left);
  setMotor(ENB, IN3, IN4, -right);
}

int Read_Eye(int pin) {
  float voltage = analogRead(pin) * (5.0 / 1023.0);
  if (voltage <= 0) return 30;
  float distance = 12.64 * pow(voltage, -1.04);
  return constrain(distance, 4.0, 30.0);
}

void Track_wall_L() {
  int front = Read_Eye(FSensor);
  int left = Read_Eye(LSensor);

  if (front <= 8 && left < 20) { MotorControl(150, -255); delay(20); }
  else {
    track_left_no_lip(200, 30, 25, 9);
    // track_left_no_lip(255, 50, 25, 9);
    if (analogRead(RSensor) >= 450) { MotorControl(-120, 120); delay(10); }
  }
  MotorControl(LeftMotor, RightMotor);
  delay(10);
}

void Track_wall_R() {
  int front = Read_Eye(FSensor);
  int right = Read_Eye(RSensor);

  if (front <= 8 && right < 20) { MotorControl(-255, 150); delay(20); }
  else {
    track_right_no_lip(200, 30, 25, 9);
    // track_right_no_lip(255, 50, 25, 9);
    if (analogRead(LSensor) >= 450) { MotorControl(120, -120); delay(10); }
  }
  MotorControl(LeftMotor, RightMotor);
  delay(10);
}

void track_left_no_lip(int BaseSpeed, float Kp, float Kd, int Target) {
  Position = Read_Eye(LSensor);
  errorL = Position - Target;

  if (lastErrorL - errorL > 8) lastErrorL = errorL;

  PowerMotor = (Kp * errorL) + (Kd * (errorL - lastErrorL));
  lastErrorL = errorL;

  PowerMotor = constrain(PowerMotor, -80, BaseSpeed);

  LeftMotor = BaseSpeed - PowerMotor;
  RightMotor = BaseSpeed + PowerMotor;

  if (LeftMotor >= 255) LeftMotor = 225;
  if (LeftMotor <= 0) LeftMotor = 0;
  if (RightMotor >= 255) RightMotor = 255;
  if (RightMotor <= 0) RightMotor = 0;
}

void track_right_no_lip(int BaseSpeed, float Kp, float Kd, int Target) {
  Position = Read_Eye(RSensor);
  errorR = Position - Target;

  if (lastErrorR - errorR > 8) lastErrorR = errorR;

  PowerMotor = (Kp * errorR) + (Kd * (errorR - lastErrorR));
  lastErrorR = errorR;

  PowerMotor = constrain(PowerMotor, -80, BaseSpeed);

  LeftMotor = BaseSpeed + PowerMotor;
  RightMotor = BaseSpeed - PowerMotor;

  if (LeftMotor >= 255) LeftMotor = 225;
  if (LeftMotor <= 0) LeftMotor = 0;
  if (RightMotor >= 255) RightMotor = 255;
  if (RightMotor <= 0) RightMotor = 0;
}

void view() {
  while (true) {
    Serial.print("\tL    : "); Serial.print(analogRead(LSensor)); Serial.print("\t");
    Serial.print("\tF    : "); Serial.print(analogRead(FSensor)); Serial.print("\t");
    Serial.print("\tR    : "); Serial.print(analogRead(RSensor)); Serial.print("\t");
    Serial.print("\tM    : "); Serial.println(analogRead(MSensor));
    Serial.print("\tL-CM : "); Serial.print(Read_Eye(LSensor)); Serial.print("\t");
    Serial.print("\tF-CM : "); Serial.print(Read_Eye(FSensor)); Serial.print("\t");
    Serial.print("\tR-CM : "); Serial.println(Read_Eye(RSensor));
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
