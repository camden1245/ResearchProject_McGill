// settings.h

// limit switch pins
#define forwardLimitSwitchPin 2
#define rearLimitSwitchPin 3

// stepper motor_ driver pins
#define enaPin 5
#define dirPin 6
#define pulPin 7

// dc motor_ pin
#define escPin 9

// syringe pump pins
#define
#define

// Distance settings
const long homeTravelDistance = 3000;					// travel distance to home, change accordingly
const long stepsToGetOffLimitSwitchDuringHoming = 600; 	// steps to back off the limit switch after it his hit

// Speed and acceleration settings
const float homingSpeed = 2000;  						// speed of the stage when in homing mode
const float homingAcceleration = 1000; 					// acceleration of the stage when in homing mode
const float forwardRunSpeed = 1000;  					// speed of the stage when moving forwards
const float forwardRunAcceleration = 2000;  			// acceleration of the stage when moving forwards
const float maxSpeed = 10000;  							// max speed allowed 

// Spin coating settings
const long spinCoatingTime = 1000; 						// Placeholder, set according to needs
const int numberOfLayers = 10; 							// Placeholder, set according to needs
const long positionA = 1500; 							// Placeholder for spin coater location
const long positionB = 2500; 							// Placeholder for second coating location

// DC motor_ settings
float motor_DepositRPM = 								// rpm that the dc motor_ goes when syringe pump is depositing solution on to platform
float motor_SpinCoatingRPM = 							// rpm that the dc motor_ ramps up to for spin coating
float motor_SpinCoatingTime = 							// time that the motor_ spins for during spin coating process
float motor_RampUpTime = 

const float motor_MinPulse = 1000;						// minimum pulse width for esc (us)
const float motor_MaxPulse = 2000;						// maximum pulse width for esc (us)


// syringe pump settings
const float ttlPulseDuration = 500;						// pulse duration (ms)



