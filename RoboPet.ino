#include <ESP32Servo.h>

// -------- ULTRASONIC --------
#define TRIG_PIN 4
#define ECHO_PIN 18

// -------- SERVO --------
#define SERVO_PIN 19
Servo myServo;

// -------- MOTOR DRIVER --------
#define AIN1 14
#define AIN2 27
#define PWMA 26 
#define BIN1 33
#define BIN2 25
#define PWMB 32 
#define STBY 13

// --- ADJUSTMENTS ---
const int SERVO_CENTER = 90;  
const int SWEEP_RANGE = 70;
const int SERVO_STEP = 1;
const int MOTOR_SPEED = 120; 
const int SPEED_DELAY = 40; 
int LEFT_SPEED = 160;
int RIGHT_SPEED = 200;  

int currentAngle = SERVO_CENTER;
int stepDir = SERVO_STEP; 

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);

  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50); 
  myServo.attach(SERVO_PIN, 500, 2400);
  
  myServo.write(SERVO_CENTER);
  delay(1000);
}

void loop() {
  // --- SERVO SWEEP ---
  currentAngle += stepDir;
  if (currentAngle >= (SERVO_CENTER + SWEEP_RANGE) || currentAngle <= (SERVO_CENTER - SWEEP_RANGE)) {
    stepDir = -stepDir; 
  }
  myServo.write(currentAngle);

  long distance = getDistance();
  
  // --- MOVEMENT LOGIC ---
  if (distance > 0 && distance < 15) {
    executeMove("BACKWARD");
  } 
  else if (distance > 25) {
    executeMove("FORWARD");
  } 
  else if(distance > 15 && distance < 25){
    executeMove("STOP");
  }

  delay(30);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 25000); 
  return (duration / 2) / 29.1;
}

void executeMove(String dir) {
  if (dir == "FORWARD") {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
    analogWrite(PWMA, MOTOR_SPEED); 
    analogWrite(PWMB, MOTOR_SPEED);
  } else if (dir == "BACKWARD") {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
    analogWrite(PWMA, MOTOR_SPEED); 
    analogWrite(PWMB, MOTOR_SPEED);
  } else {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, LOW);
    analogWrite(PWMA, 0); 
    analogWrite(PWMB, 0);
  }
}
