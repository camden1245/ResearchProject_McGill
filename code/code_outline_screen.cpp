#include <MCUFRIEND_kbv.h>  // For TFT display
#include <Servo.h>          // For ESC control
#include <AccelStepper.h>   // For stepper control

// TFT Display Setup
MCUFRIEND_kbv tft;
#define BLACK 0x0000
#define WHITE 0xFFFF
#define BLUE  0x001F
#define RED   0xF800
#define GREEN 0x07E0

// Define pins
const int escPin = 9;
const int stepPin = 2;
const int dirPin = 3;
const int enablePin = 4;

// Define constants
const int spinRPM = 1500;    // Adjust as needed
const int spinDuration = 5000;
const int rampUpTime = 1000;
const int positionA = 1000;
const int positionB = 2000;
const int numCycles = 5;

int completedCycles = 0; // Track the number of layers deposited

Servo esc;
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
    Serial.begin(9600);
    esc.attach(escPin);

    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, LOW);

    // Initialize TFT Display
    tft.reset();
    tft.begin(tft.readID());
    tft.setRotation(1);  // Adjust based on your screen orientation
    tft.fillScreen(BLACK);
    displayMessage("Spin Coater Ready", WHITE);
    delay(2000);
}

void loop() {
    for (int i = 0; i < numCycles; i++) {
        updateDisplay(i + 1, "Moving to Position A");
        moveLinearTranslator(positionA);

        updateDisplay(i + 1, "Spinning");
        spinCoatingProcess();

        delay(1000);

        updateDisplay(i + 1, "Moving to Position B");
        moveLinearTranslator(positionB);

        updateDisplay(i + 1, "Spinning");
        spinCoatingProcess();

        delay(1000);

        completedCycles++;
    }

    while (true) {
        updateDisplay(completedCycles, "Process Complete");
    }
}

void moveLinearTranslator(int targetPosition) {
    stepper.moveTo(targetPosition);
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
    delay(500);
}

void spinCoatingProcess() {
    for (int throttle = 1000; throttle <= map(spinRPM, 0, 2000, 1000, 2000); throttle += 10) {
        esc.writeMicroseconds(throttle);
        delay(rampUpTime / 100);
    }

    delay(spinDuration);

    for (int throttle = map(spinRPM, 0, 2000, 1000, 2000); throttle >= 1000; throttle -= 10) {
        esc.writeMicroseconds(throttle);
        delay(rampUpTime / 100);
    }

    esc.writeMicroseconds(1000);
}

// Display messages on the screen
void displayMessage(const char *message, uint16_t color) {
    tft.fillScreen(BLACK);
    tft.setCursor(50, 100);
    tft.setTextColor(color);
    tft.setTextSize(2);
    tft.print(message);
}

// Update display with routine info
void updateDisplay(int cycle, const char *routine) {
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    
    tft.setCursor(50, 50);
    tft.print("Cycle: ");
    tft.print(cycle);
    tft.print("/");
    tft.print(numCycles);

    tft.setCursor(50, 100);
    tft.print("Routine: ");
    tft.print(routine);
}