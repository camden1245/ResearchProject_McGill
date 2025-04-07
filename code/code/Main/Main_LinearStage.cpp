// linearstage.cpp
#include "settings.h"
#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void linearStage_Setup() {
    /*
    Setup function for the linear stage

    initalize all the pins, then write ENABLE pin to HIGH to enable the motor. 
    
    it then calls homeStage(), the function that homes the linear stage, establishing a '0' position for
    future reference.

        - Called in setup()
    */
    delay(7000);
    Serial.begin(9600);
    pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(ENA_PIN, OUTPUT);
    digitalWrite(ENA_PIN, HIGH);

    stepper.setMaxSpeed(maxSpeed);
	homeStage();
    /* 
	for testing:
	lines 20-25 removed when ran with all files. 
	*/
    delay(2000);
    moveToPosition(POSITION_A);
    delay(5000);
    moveToPosition(POSITION_B);
    delay(5000);
    moveToPosition(POSITION_A);
    
}

void loop() {
  
}

void homeStage() {
    /*
    Homing function for the linear stage

    sets acceleration and speed to homing presets (adjust in Main_Settings.hpp)
    Moves the motor indefinetly while the limit switch is not activated (logic HIGH)

    Once limit swtich is hit (logic LOW) the motor stops, and sets the current position as position 0. 
    - soon to implement: testing to find the far RIGHT side of the stage, set this as x steps, once it reaches x-50, stop the 
      motor as a safety factor.

    Homing is now complete.
    
        - Called in linearStage_Setup()
    */
    
    stepper.setAcceleration(8000);
    Serial.println("Homing...");
    stepper.setMaxSpeed(homingSpeed);
    stepper.moveTo(1000000);  // Move indefinitely towards the limit switch

    while (digitalRead(LIMIT_SWITCH_PIN) == HIGH) {
        stepper.run();
    }

    stepper.stop();
    delay(100);
	
    stepper.setCurrentPosition(0); // Set zero reference
    Serial.println("Homing Complete.");
    Serial.println("*---------------------------------------------*");
}

void moveToPosition(int position) {
    /*
    Move function for linear stage

    when called, with arguements PositionA or PositonB (defined in Main_Settings.hpp),
    the stage will move the allocated amount of steps to each positon.These positions need to
    be manually calculated. find positon A, where syringe A is directly above the coating platform,
    then do the same for position B. 
    
        - Called in loop()
    */
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
    Serial.println("*---------------------------------------------*");
}