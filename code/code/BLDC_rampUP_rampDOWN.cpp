#include <Servo.h>

Servo esc;

const int minPulse = 1000;
const int maxPulse = 2000;
const int escPin = 9;
const int maxRPM = 10800; // 12 VDC * 900 KV rating


void setup() {
  // put your setup code here, to run once:
  esc.attach(escPin, minPulse, maxPulse);
  Serial.begin(9600);
  delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int targetRPM = 5000;
  int targetPulse = map(targetRPM, 0, maxRPM, minPulse, maxPulse);
  targetPulse = constrain(pulse, minPulse, maxPulse);

  // RAMP UP
  for (int pulse = minPulse; pulse <= targetPulse; pulse += 5) {
    esc.writeMicroseconds(pulse);
    Serial.print("Ramping Up - Pulse: ");
    Serial.println(pulse);
    delay(50);
  }
  delay(2000);
  //RAMP DOWN
  for(int pulse = targetPulse; pulse <= minPulse; pulse -= 5);{
    esc.writeMicroseconds(pulse);
    Serial.print("ramping down - pulse: ");
    Serial.print(pulse);
    delay(50);
  }
}