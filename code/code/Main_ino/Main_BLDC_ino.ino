// BLDCrampuprampdown.cpp
//#include "settings.h"
#include <Servo.h>

Servo esc;

void motorSetup() {
  esc.attach(ESC_PIN, minPulse, maxPulse);
  esc.writeMicroseconds(minPulse);   // Step 1: Minimum throttle
  delay(1000);                        // Wait 1 sec
  esc.writeMicroseconds(maxPulse);   // Step 2: Maximum throttle
  delay(1000);                        // Wait 1 sec
  esc.writeMicroseconds(minPulse);   // Step 3: Back to minimum
  delay(1000);                        // Wait 1 sec
  delay(5000);
  Serial.println(F("ESC Armed"));
}

void motorLoop() {
	/*
	loop for the motor  to ramp up to a value, TARGET_RPM, then ramp back down to idle
	
	TARGET_RPM is the rpm the motor will ramp to; from the MAX_RPM in settings, it is found by a mapping function, 
	using the min/max pulses, and the min (0) and max (9480) rpm allowed from the motor. 
	
	ramping is done by incrementing a value: pulse, then writing the motor that pulse value. 
	the ramping can be adjusted by changing the increment value (" ; pulse += 5") or the short delay (50ms), to make
	it slower or faster
	
	there is a delay inbetween the ramp up and the ramp down, this delay can be changed in settings depending on 
	long the coating should occur
	*/
	
  unsigned int TARGET_RPM = 7000;
  unsigned int targetPulse = map(TARGET_RPM, 0, maxRPM, minPulse, maxPulse);
  targetPulse = constrain(targetPulse, minPulse, maxPulse);

  // RAMP UP
  for (int pulse = minPulse; pulse <= targetPulse; pulse += 5) {
    esc.writeMicroseconds(pulse);
    Serial.print(F("Ramping Up - Pulse: "));
    Serial.println(pulse);
    delay(50);
  }
  delay(MOTOR_SPIN_COATING_TIME);
  //RAMP DOWN
  for(int pulse = targetPulse; pulse >= minPulse; pulse -= 5){
    esc.writeMicroseconds(pulse);
    Serial.print(F("ramping down - pulse: "));
    Serial.println(pulse);
    delay(50);
  }
}
