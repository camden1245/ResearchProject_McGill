// syringe pump control

/*
code to turn on pump, pump settings must be set on the device. 


Currently -- 6:27, 2025-03-19
	-configuration of Syringe pump has it so that the Falling Edge of trigger pin signal
	-(ie writing trigger pin to ttl logic "LOW" 0-0.8V coming from "HIGH" (2-5V) would 
	-turn the motor on
	
	-with this configuration, and the current pumping program settings (described below), 
	-the "dispense volume" function will run the pump so that it will go through 1 Pumping Program
	-then wait until it is called again. 
	-there might need to be some changes with the time delays, depending on how long it takes for the
	-acutual Pumping Program to run.

Wiring/Pinout:
Pin 1: VCC
Pin 2: Trigger
Pin 8: Direction
Pin 9: GND	
	
How to Set a Pumping Program:
1.	Press and hold the 'Rate' key until phase number is shown (PH:nn)
2. 	Select Phase 1 (PH:01)
3. 	Press and hold the 'Volume' key until it displays the Program Function
4. 	Press the arrow keys to select the 'RATE' function. 
5. 	Press the 'Rate' key. Use the arrows to select the rate for dispensing.
6. 	Press 'Volume' key. Use arrow keys to select the volume to be dispensed. 
7. 	Optional: Press the withdraw key to set the direction (withdraw/infuse)
8. 	** needed for this configuration ** Create second phase by holding 'Rate' key and use arrows to select (PH:02)
9. 	Hold 'Volume' and use the arrows to navigate to 'STOP' - the stop function tells the machine to wait for the next
	until it starts pumping again. This next trigger will be given for the next cycle. 
	
	
Current  (example) Pumping Program: 
	PHASE: 01
	Diameter: 					20.00mL
	Rate: 						500mL/hr
	Volume to be Dispensed:		1.5mL
	PHASE: 02
	Volume set to STOP
	
	
TTL Operational Trigger Settings
	TR:St (Start only) : Trigger Input Falling Edge -> this means, logic "HIGH" is Idle mode, "LOW" is Run. 
		- Hold the "Diameter" key, wait until the screen shows "ttl" then click an arrow key, then select "tr:St"



*/


# define triggerPin 2
# define directionPin 3

void syringe_pump_setup() {
	//attach pins
	pinMode(triggerPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	delay(100);
	digitalWrite(triggerPin, HIGH);
	
}

void dispenseVolume(){
	digitalWrite(triggerPin, LOW);
	delay(100);
	digitalWrite(triggerPin, HIGH);
	//include delay ~10,000 ms after running dispenseVolume fucntion
	delay(10000);
}