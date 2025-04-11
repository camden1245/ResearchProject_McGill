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
const uint16_t maxSpeed = 750;
const int16_t POSITION_A = -5000; 			  		// depositing location A
const int16_t POSITION_B = -6000;					  	// depositing location B
const uint16_t homingSpeed = 750;				  		// speed the motor moves when in homing
const uint16_t acceleration = 1000;						// acceleration of the linear stage					


// Spin coating settings
const uint8_t NUMBER_OF_LAYERS = 10;					// number of layers 


// DC Motor settings
const uint16_t MOTOR_SPIN_COATING_RPM = 3000;			// desired rpm for spin coating (value to ramp up to)
const uint16_t MOTOR_SPIN_COATING_TIME = 5000;			// duration after motor ramps up to desired rpm, ms
const uint16_t minPulse = 1000;					// min pulse for motor (1000, 2000)
const uint16_t maxPulse = 2000;					// max pulse for motor (1000, 2000)
const uint16_t maxRPM = 9480;							// max rpm of motor, 790KV * 12 V

#endif

