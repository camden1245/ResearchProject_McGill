// settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

// Limit switch pins
# define LIMIT_SWITCH_PIN

// Stepper motor driver pins
#define ENA_PIN 5
#define DIR_PIN 6
#define PUL_PIN 7

// DC Motor pin
#define ESC_PIN 9

// Syringe pump pins
#define TRIGGER_PIN 10
#define DIRECTION_PIN 11

// Linear stage settings
const long POSITION_A = 1500;						// depositing location A
const long POSITION_B = 2500;						// depositing location B
const int HOMING_SPEED = 3000;						// speed the motor moves when in homing
const int ACCELERATION = 5000;						// acceleration of the linear stage					


// Spin coating settings
const int NUMBER_OF_LAYERS = 10;					// number of layers 


// DC Motor settings
const float MOTOR_SPIN_COATING_RPM = 3000;			// desired rpm for spin coating (value to ramp up to)
const float MOTOR_SPIN_COATING_TIME = 5000;			// duration after motor ramps up to desired rpm, ms
const float MOTOR_MIN_PULSE = 1000;					// min pulse for motor (1000, 2000)
const float MOTOR_MAX_PULSE = 2000;					// max pulse for motor (1000, 2000)
const int MAX_RPM = 9480;							// max rpm of motor, 790KV * 12 V

#endif