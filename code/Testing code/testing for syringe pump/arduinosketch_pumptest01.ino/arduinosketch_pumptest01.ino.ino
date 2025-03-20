// syringe pump control

/*
code to turn on pump, pump settings must be set on the device. 

*/


const int triggerPin = 2;

void setup() {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, HIGH);  // Idle high (required for 'St' mode)
  Serial.begin(9600);
  Serial.println("Ready for dispense trigger");
}

void loop() {
  // When ready to dispense, send falling edge
  dispenseVolume();

  // Wait for next cycle (example 10s)
  delay(10000);
}

void dispenseVolume() {
  Serial.println("Triggering dispense...");
  digitalWrite(triggerPin, LOW);   // Falling edge
  delay(100);                     // 100 ms pulse
  digitalWrite(triggerPin, HIGH);  // Back to idle high
}
