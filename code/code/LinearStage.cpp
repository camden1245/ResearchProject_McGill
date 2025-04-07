#include <AccelStepper.h>

// Pin Definitions
const int stepPin = 2;
const int dirPin = 3;
const int enaPin = 4;
const int limitSwitchPin = 5;  // Normally Open (NO) limit switch

// Motion Parameters
const int backoffSteps = -50; // Steps to move off the limit switch after homing
const int homingSpeed = 5000;
const int maxSpeed = 3000;
const int acceleration = 2500;

// Positions
const int positionA = 10000;
const int positionB = 12000;

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
    delay(7000);
    Serial.begin(9600);
    pinMode(limitSwitchPin, INPUT_PULLUP);
    pinMode(enaPin, OUTPUT);
    digitalWrite(enaPin, HIGH); // Enable stepper driver

    stepper.setMaxSpeed(maxSpeed);
    
    
    
    homeStage();
    delay(2000);
    moveToPosition(positionA);
    delay(1000);
    moveToPosition(positionB);
    delay(5000);
    moveToPosition(positionA);
    
}

void loop() {
  
}

void homeStage() {
    stepper.setAcceleration(8000);
    Serial.println("Homing...");
    stepper.setMaxSpeed(homingSpeed);
    stepper.moveTo(1000000);  // Move indefinitely towards the limit switch

    while (digitalRead(limitSwitchPin) == HIGH) {
        stepper.run();
    }

    stepper.stop();
    delay(100);

    stepper.moveTo(backoffSteps); // Move off the limit switch
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }

    stepper.setCurrentPosition(0); // Set zero reference
    Serial.println("Homing Complete.");
}

void moveToPosition(int position) {
    stepper.setAcceleration(10000);
    Serial.print("Moving to Position: ");
    Serial.println(position);
    stepper.moveTo(position);
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
    Serial.print("Final Step Position: ");
    Serial.println(stepper.currentPosition());
    Serial.println("Position reached.");
}