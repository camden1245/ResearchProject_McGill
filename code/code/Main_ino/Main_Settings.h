// settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

// Limit switch pins
# define LIMIT_SWITCH_PIN 5

// Stepper motor driver pins
#define ENA_PIN 4
#define DIR_PIN 3
#define PUL_PIN 2

// DC Motor pin
#define ESC_PIN 9

// Syringe pump pins
#define TRIGGER_PIN 10


// Linear stage settings
const int maxSpeed = 750;
const int POSITION_A = -5000; 			  		// depositing location A
const int POSITION_B = -6000;						// depositing location B
const int homingSpeed = 750;				  		// speed the motor moves when in homing
const int acceleration = 1000;						// acceleration of the linear stage					


// Spin coating settings
const int NUMBER_OF_LAYERS = 10;					// number of layers 


// DC Motor settings
const int MOTOR_SPIN_COATING_RPM = 3000;			// desired rpm for spin coating (value to ramp up to)
const int MOTOR_SPIN_COATING_TIME = 5000;			// duration after motor ramps up to desired rpm, ms
const int minPulse = 1000;					// min pulse for motor (1000, 2000)
const int maxPulse = 2000;					// max pulse for motor (1000, 2000)
const int maxRPM = 9480;							// max rpm of motor, 790KV * 12 V

#endif

