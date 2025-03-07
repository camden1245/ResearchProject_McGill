// Setup.h
#include <AccelStepper.h>
AccelStepper stepper(AccelStepper::DRIVER, pulPin, dirPin);

const int notHomed = 0;
const int homed = 1;
const int error = 3;
const int pressedDuringHome = 4;
int homeStatus = notHomed;