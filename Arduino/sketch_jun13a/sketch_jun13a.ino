#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(4, 5); // Arduino RX=4, TX=5
DFRobotDFPlayerMini player;

// LEFT SENSOR
const int trigL = 2;
const int echoL = 3;

// CENTER (FRONT) SENSOR
const int trigC = 9;
const int echoC = 10;

// RIGHT SENSOR
const int trigR = 12;
const int echoR = 13;

// OUTPUTS
const int buzzer = 8;
const int led = 7;

// DISTANCE LIMIT (in cm)
const int limit = 50;

long readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void alertAndSpeak(int fileNo) {
  digitalWrite(led, HIGH);

  tone(buzzer, 1000);
  delay(2000);           // Buzzer beeps for 2 seconds
  noTone(buzzer);

  player.play(fileNo);   // Play voice (0001.mp3, 0002.mp3 or 0003.mp3)
  delay(1800);           // Wait for voice to finish

  digitalWrite(led, LOW);
}

void setup() {
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing DFPlayer...");
  if (!player.begin(mySerial)) {
    Serial.println("DFPlayer NOT found! Check wiring, SD card & resistor.");
  } else {
    Serial.println("DFPlayer Ready!");
  }

  player.volume(20);   // Start with volume 20 (you can increase later)

  Serial.println("Smart Blind Stick Ready");
}

void loop() {
  int distL = readDistance(trigL, echoL);
  int distC = readDistance(trigC, echoC);
  int distR = readDistance(trigR, echoR);

  // FRONT has HIGHEST priority (most important for blind person)
  if (distC <= limit) {
    alertAndSpeak(2);           // 0002.mp3 → "Front"
  } 
  else if (distL <= limit) {
    alertAndSpeak(1);           // 0001.mp3 → "Left"
  } 
  else if (distR <= limit) {
    alertAndSpeak(3);           // 0003.mp3 → "Right"
  } 
  else {
    digitalWrite(led, LOW);
  }

  delay(80);   // Small delay
}
