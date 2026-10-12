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

void setup() {
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  pinMode(trigC, OUTPUT); pinMode(echoC, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(buzzer, OUTPUT); pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Testing All 3 Sensors (No DFPlayer)");
}

void loop() {
  int distL = readDistance(trigL, echoL);
  delay(60);
  int distC = readDistance(trigC, echoC);
  delay(60);
  int distR = readDistance(trigR, echoR);
  delay(60);

  Serial.print("L:"); Serial.print(distL);
  Serial.print("  C:"); Serial.print(distC);
  Serial.print("  R:"); Serial.println(distR);

  if (distC <= limit) {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);
    delay(2000);
    noTone(buzzer);
    digitalWrite(led, LOW);
  } 
  else if (distL <= limit) {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);
    delay(2000);
    noTone(buzzer);
    digitalWrite(led, LOW);
  } 
  else if (distR <= limit) {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);
    delay(2000);
    noTone(buzzer);
    digitalWrite(led, LOW);
  } 
  else {
    digitalWrite(led, LOW);
  }
}
