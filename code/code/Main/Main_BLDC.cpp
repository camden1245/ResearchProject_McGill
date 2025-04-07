// BLDCrampuprampdown.cpp
#include "settings.h"
#include <Servo.h>

Servo esc;

void motorSetup() {
    esc.attach(ESC_PIN, MOTOR_MIN_PULSE, MOTOR_MAX_PULSE);
	delay(10000);
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
	
  int TARGET_RPM = 5000;
  int targetPulse = map(TARGET_RPM, 0, maxRPM, MOTOR_MIN_PULSE, maxPulse);
  targetPulse = constrain(pulse, MOTOR_MIN_PULSE, maxPulse);

  // RAMP UP
  for (int pulse = MOTOR_MIN_PULSE; pulse <= targetPulse; pulse += 5) {
    esc.writeMicroseconds(pulse);
    Serial.print("Ramping Up - Pulse: ");
    Serial.println(pulse);
    delay(50);
  }
  delay(MOTOR_SPIN_COATING_TIME);
  //RAMP DOWN
  for(int pulse = targetPulse; pulse <= MOTOR_MIN_PULSE; pulse -= 5);{
    esc.writeMicroseconds(pulse);
    Serial.print("ramping down - pulse: ");
    Serial.print(pulse);
    delay(50);
  }
}