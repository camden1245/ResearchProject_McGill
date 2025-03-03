// NE-1000 Syringe Pump Test Code
// RS232 to TTL Communication
#include <SoftwareSerial.h>

#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial syringePump(RX_PIN, TX_PIN);

void setup() {
  syringePump.begin(19200);  // Baud rate for NE-1000 pump
  Serial.begin(9600);
  delay(1000);
  syringePump.print("RUN\r");  // Start the pump
  Serial.println("Pump started");
}

void loop() {
  delay(5000);
  syringePump.print("STP\r");  // Stop the pump
  Serial.println("Pump stopped");
  delay(5000);
}