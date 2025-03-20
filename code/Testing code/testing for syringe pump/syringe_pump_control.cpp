// syringe pump control

/*
code to turn on pump, pump settings must be set on the device. 

*/


# define triggerPin 2
# define directionPin 3

void setup() {
	//attach pins
	pinMode(triggerPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	delay(100);
	
	serial.begin(9600);
	serial.println("Pins configured");
	
}

void loop() {
}