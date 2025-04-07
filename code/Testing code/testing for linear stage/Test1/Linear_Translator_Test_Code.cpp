const int PUL=7;
const int DIR=6;
const int ENA=5;
const int step_per_rev=400;

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  
}

void loop() {
  for (int i=0; i<step_per_rev; i++) {
    digitalWrite(DIR, LOW);
    digitalWrite(PUL, HIGH);
    digitalWrite(ENA, HIGH);
    delayMicroseconds(1000);
    digitalWrite(PUL, LOW);
    delayMicroseconds(1000);
  }
  delay(2000);
  for (int i=0; i<step_per_rev; i++) {
    digitalWrite(DIR, HIGH);
    digitalWrite(PUL, HIGH);
    digitalWrite(ENA, HIGH);
    delayMicroseconds(1000);
    digitalWrite(PUL, LOW);
    delayMicroseconds(1000);
  }
  delay(2000);
  }