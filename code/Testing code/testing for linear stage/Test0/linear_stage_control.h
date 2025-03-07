// Setup.h
#include <AccelStepper.h>
#include "settings.h"
AccelStepper stepper(AccelStepper::DRIVER, pulPin, dirPin);

const int notHomed = 0;
const int homed = 1;
const int error = 3;
const int pressedDuringHome = 4;
int homeStatus = notHomed;

void rearLimitHit(){
	if (homedStatus =! pressedDuringHome){
		delay(20);
		if (digitalRead(rearLimitSwitchPin) == LOW){
			if (homedStatus == notHomed){
				homedStatus = pressedDuringHome;
			}
			// if it is already homed, and it hits the rear limit switch, there is an issue -> stop the motor__ and reset
			if (homedStatus == homed) {
				digitalWrite(enaPin, LOW);
				homeStatus=error;
			}
		}
	}
}
void forwardLimitHit(){
	delay(20) //debounce
	if (digitalRead(forwardLimitSwitchPin) == LOW){
		// set this as an error, the forward pin should not ever be hit
		digitalWrite(enaPin,LOW); // stop the motor__
		homedStatus = error;
	}
}
void linearStage_Setup(){
	serial.begin(9600);
	delay(500);
	// set limit switches as input pullups
	pinMode(forwardLimitSwitchPin,INPUT_PULLUP);
	pinMode(rearLimitSwitchPin,INPUT_PULLUP);
	// attach interrupt pins to handlers
	attachInterrupt(digitalPinToInterrupt(forwardLimitSwitchPin),forwardLimitHit,FALLING);
	attachInterrupt(digitalPinToInterrupt(rearLimitSwitchPin), rearLimitHit,FALLING);
	//accel stepper setup
	stepper.enablePin(enaPin);
	
	stepper.setMaxSpeed(maxSpeed);
	stepper.setMaxAcceleration(homingAcceleration);
}
void homeStage(){
	digitalWrite(enaPin,HIGH);
	stepper.setMaxSpeed(homingSpeed);
	stepper.moveTo(-homeTravelDistance);
	
	while (homedStaus != homed){
		stepper.run();
		if (homedStatus = pressedDuringHome){
			stepper.stop();
			stepper.setCurrentPosition(0);
			stepper.moveTo(-stepsToGetOffLimitSwitchDuringHoming);
			while (stepper.distanceToGo != 0){
				stepper.run();
			}
			stepper.setCurrentPosition(0);
			homedStatus = homed;
			serial.println("Homed");
		}
	}
}
