// Linear Translator Test Code
// NEMA23 Stepper Motor
#include <AccelStepper.h>

#define STEP_PIN 2
#define DIR_PIN 3
#define MAX_SPEED 1000
#define ACCELERATION 500

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(ACCELERATION);
}

void loop() {
  stepper.moveTo(1000);  // Move forward
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000);

  stepper.moveTo(0);  // Move backward
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(1000);
}
