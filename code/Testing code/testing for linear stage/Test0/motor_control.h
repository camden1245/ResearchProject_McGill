//motor_control.h
#include "settings.h"
#include "setup.h"
#include <servo.h>

void motorSetup(){
	esc.attach(escPin, motorMinPulse, motorMaxPulse);
	delay(1000);
	
	esc.writeMicroseconds(motorMinPulse);
	delay(2000);
}
void rampMotor(int motorTargetRPM, int motorRampUpTime){
	int motorCurrentRPM = motorMinPulse;
	int step = (targetRPM - motorMinPulse)/(motorRampUpTime/10);
	
	while (motorCurrentRPM <= motorTargetRPM){
			esc.writeMicroseconds(motorCurrentRPM);
			motorCurrentRPM += step;
			delay(10);
	}
	esc.writeMicroseconds(motorTargetRPM);
}
void stopMotor(){
  esc.writeMicroseconds(motorMinPulse);
  delay(1000);
}
void motorRoutine(){
	rampMotor(motorDepositRPM, 2000);
	
	// deposit syringe pump
	
	rampMotor(motorSpinCoatingRPM, 3000);
	delay(spinCoatingTime);
	stopMotor();
}
