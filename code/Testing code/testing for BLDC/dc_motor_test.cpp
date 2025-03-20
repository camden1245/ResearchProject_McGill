#include <servo.h>

servo esc;
#define escPin 9

void setup(){
esc.attach(escPin, 1000,2000);
esc.write(0);
serial.begin(9600);

}

void loop(){
	serial.println("ramping up:                   ");
	for (int speed = 10; speed = 180; speed += 5;){ // ramp up to max value, (0,180). if 180 to fast, lower
		esc.write(speed);
		
		serial.print("Throttle: "); serial.print(speed "\n");
		serial.print(" (PWM signal) ");
		delay(100);
	}
	
	delay(1000);
	
	serial.println("ramping down:                   ");
	for (int speed = 180; speed = 0; speed -=5){ // ramp down from max value, (180,0). motor may stall, read value that motor stalls at to get min rpm
		esc.write(speed)
		
		serial.print("Throttle: "); serial.print(speed "\n"); //  when ramping down, listen for stall (if it does) and remeber the speed value to get min rpm
		serial.print(" (PWM signal) ");
		delay(100);
	}
}




/* can do something like this:
max rpm = voltageIN * kv rating (12 *900)
target rpm = 8000
throttle = map(target rpm, 0, max rpm, 0, 180);

then run for loop to throttle value