#include <stdint.h>
#include "Main_Settings.h"    // Configurations and settings for the project
#include "prototypes.h"       // Required for function prototypes and StatusMsg enum
#include <Arduino.h>           // Arduino core library for basic functions

#ifdef __AVR__ // Check for AVR architecture (e.g., Arduino Uno)
int freeMemory() {
    extern int __heap_start, *__brkval;
    int v; // Stack variable (top of stack)
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif

/*
Setup function to initialize all components:

    - Starts the serial communication
    - Prints available memory
    - Sets up the OLED screen
    - Initializes components: linear stage, motor, syringe pump

    Called once during startup.
*/
void setup() {
    Serial.begin(9600);
    Serial.print(F("Free memory at startup: "));
    Serial.println(freeMemory());                          // Print available memory at startup

    screen_setup();                                        // Initialize the OLED screen
    linearStage_Setup();                                   // Set up the linear stage
    motorSetup();                                          // Set up the motor
    syringePump_Setup();                                   // Set up the syringe pump

    Serial.println(F("Setup process complete"));
}


void loop() {

     /*
      Main loop of the program, runs continuously:

        - Alternates between position A and position B, dispensing solution, and spinning substrate
        - Updates the OLED screen with the current status, cycle number, and progress
        - Uses the `moveToPosition`, `dispenseVolume`, and `motorLoop` functions to control the hardware

    Called repeatedly during operation.
    */
    Serial.print(F("Free memory in loop: "));
    Serial.println(freeMemory());                           // Print available memory during each loop iteration
    delay(1000);                                            // Delay for stability

    static bool positionAtA = true;                         // Track the current position (A or B)

    // Loop through the number of layers (process for each layer)
    for (int i = 1; i < NUMBER_OF_LAYERS; i++) {
        int currentCycle = i;                               

        // Determine the current position (A or B) as a string
        String pos = positionAtA ? "A" : "B";
        unsigned short int progress = map(i, 0, NUMBER_OF_LAYERS, 0, 100); // Progress percentage

        // Update the screen with the current status message
        char statusBuffer[50];                               
        getStatusMessage(statusBuffer, MSG_MOVING_TO_POS, pos.c_str());
        updateScreen(statusBuffer, currentCycle, progress);

        moveToPosition(positionAtA ? POSITION_A : POSITION_B); 
        getStatusMessage(statusBuffer, MSG_AT_POS, pos.c_str());
        updateScreen(statusBuffer, currentCycle, progress);

        delay(1000); 

        Serial.println(F("Syringe Pump Starting"));
        getStatusMessage(statusBuffer, MSG_DISPENSING, pos.c_str()); 
        updateScreen(statusBuffer, currentCycle, progress);
        dispenseVolume(); // Dispense solution using the syringe pump
        Serial.println(F("Syringe Pump Finished"));

        delay(1000); // Short delay after dispensing

        getStatusMessage(statusBuffer, MSG_SPINNING); // Spinning status
        updateScreen(statusBuffer, currentCycle, progress);
        motorLoop(); // Activate motor loop for spinning
        Serial.println(F("Motor loop finished"));

        delay(1000); // Short delay after spinning

        positionAtA = !positionAtA; // Toggle between positions A and B
    }

    // Final delay after the process is complete
    delay(10000); // Wait for a while before restarting the process
}
