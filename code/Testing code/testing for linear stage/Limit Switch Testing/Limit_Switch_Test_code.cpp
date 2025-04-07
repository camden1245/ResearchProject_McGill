const int limitSwitchPin = 7;  // NO side connected to D7
bool switchPressed = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // 50 ms debounce time

void setup() {
  pinMode(limitSwitchPin, INPUT_PULLUP);  // Internal pull-up
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(limitSwitchPin);

  // If the switch is pressed (LOW), start debounce timer
  if (reading == LOW && !switchPressed && (millis() - lastDebounceTime) > debounceDelay) {
    Serial.println("Limit Switch PRESSED");
    switchPressed = true;
    lastDebounceTime = millis();
  }

  // Reset the switch state when released
  if (reading == HIGH && switchPressed && (millis() - lastDebounceTime) > debounceDelay) {
    switchPressed = false;
    lastDebounceTime = millis();
  }
}
