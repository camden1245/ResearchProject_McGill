#define DIR_PIN 9    // Direction pin
#define STEP_PIN 8   // Pulse (Step) pin
#define STEPS_PER_REV 400  // Full step for NEMA 23 (1.8° step angle)

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Stepper Motor Test");
}

void loop() {
  // Rotate Clockwise
  digitalWrite(DIR_PIN, HIGH);  // Set direction
  Serial.println("Clockwise");
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);  // Correct function name
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);  // Correct function name
  }
  
  delay(1000);  // Pause before changing direction

  // Rotate Counterclockwise
  digitalWrite(DIR_PIN, LOW);
  Serial.println("Counterclockwise");
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }
  
  delay(1000);  // Pause before repeating
}