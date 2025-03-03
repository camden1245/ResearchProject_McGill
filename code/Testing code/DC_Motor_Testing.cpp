// Brushless Motor Test Code
// ESC Control
#include <Servo.h>

#define ESC_PIN 9

Servo esc;

void setup() {
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(1000);  // Initialize ESC at minimum throttle
  delay(2000);  // Give ESC time to arm
}

void loop() {
  for (int speed = 1000; speed <= 2000; speed += 10) {  // Ramp up
    esc.writeMicroseconds(speed);
    delay(50);
  }

  delay(1000);

  for (int speed = 2000; speed >= 1000; speed -= 10) {  // Ramp down
    esc.writeMicroseconds(speed);
    delay(50);
  }

  delay(1000);
}