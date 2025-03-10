#include <SoftwareSerial.h>

// Define the software serial pins
#define RX_PIN 7
#define TX_PIN 6

// Create a SoftwareSerial object
SoftwareSerial syringePump(RX_PIN, TX_PIN);

void setup() {
  // Start the hardware serial for debugging
  Serial.begin(9600);

  // Start the software serial for the syringe pump
  syringePump.begin(9600);

  Serial.println("Arduino Ready");
}

void loop() {
  // Forward commands from the PC to the pump
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');  // Read command from PC
    syringePump.print(command + "\r\n");           // Send command to the pump
  }

  // Forward responses from the pump to the PC
  if (syringePump.available()) {
    String response = syringePump.readStringUntil('\n');  // Read response from pump
    Serial.print(response);                               // Send response to PC
  }
}
