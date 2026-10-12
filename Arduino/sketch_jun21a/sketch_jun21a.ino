#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(4, 5);
DFRobotDFPlayerMini player;

const int trigL = 2, echoL = 3;
const int trigC = 9, echoC = 10;
const int trigR = 12, echoR = 13;
const int buzzer = 8, led = 7;
const int limit = 50;

long readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999;

  long dist = duration * 0.034 / 2;
  if (dist < 3 || dist > 400) return 999;
  return dist;
}

void alertAndSpeak(int fileNo) {
  digitalWrite(led, HIGH);
  tone(buzzer, 1000);
  delay(2000);
  noTone(buzzer);
  player.play(fileNo);
  delay(1800);
  digitalWrite(led, LOW);
}

void setup() {
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  pinMode(trigC, OUTPUT); pinMode(echoC, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(buzzer, OUTPUT); pinMode(led, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!player.begin(mySerial)) {
    Serial.println("DFPlayer NOT found");
  } else {
    Serial.println("DFPlayer Ready");
  }
  player.volume(18);
  Serial.println("=== Smart Blind Stick Debug Mode ===");
}

void loop() {
  int distL = readDistance(trigL, echoL);
  delay(80);
  int distC = readDistance(trigC, echoC);
  delay(80);
  int distR = readDistance(trigR, echoR);
  delay(80);

  // Print distances so we can see what is happening
  Serial.print("Left: "); Serial.print(distL);
  Serial.print("   Front: "); Serial.print(distC);
  Serial.print("   Right: "); Serial.println(distR);

  if (distC <= limit) {
    Serial.println(">>> FRONT DETECTED");
    alertAndSpeak(2);
  } 
  else if (distL <= limit) {
    Serial.println(">>> LEFT DETECTED");
    alertAndSpeak(1);
  } 
  else if (distR <= limit) {
    Serial.println(">>> RIGHT DETECTED");
    alertAndSpeak(3);
  } 
  else {
    digitalWrite(led, LOW);
  }
}
