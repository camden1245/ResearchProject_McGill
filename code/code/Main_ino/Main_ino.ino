// Main.cpp
//#include "Main_Settings_ino.ino"
//#include "Main_LinearStage_ino.ino"
//#include "Main_BLDC_ino.ino"
//#include "Main_SyringePump_ino.ino"
#include "Main_Settings.h"
#include "prototypes.h"
#include <Arduino.h>

#ifdef __AVR__
int freeMemory() {
  extern int __heap_start, *__brkval;
  int v; // Stack variable (top of stack)
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif

void setup() {
	/*
	Initialize all components
	*/
	
    Serial.begin(9600);
    Serial.print(F("Free memory at startup: "));
    Serial.println(freeMemory());
    screen_setup();
    //updateScreen("System Initialized",0,0);

    linearStage_Setup();
    motorSetup();
    syringePump_Setup();
    
    Serial.println(F("setup process complete"));
}




void loop() {
	/* loop for predetermined number of layers, 
	loop 1: 'position at A': 1
	
	move to position A, dispenseVolume, motorLoop, then write 'position at A' 1 -> 0
	
	loop 2: 'position at A': 0
	
	move to position B, dispenseVolume, motorLoop, then write 'position at A' 0 -> 1
	
	Then repeat
	*/
	
	//move to position
  Serial.print(F("Free memory in loop: "));
  Serial.println(freeMemory());
  delay(1000);



    static bool positionAtA = true;
    
    for (int i = 1; i < NUMBER_OF_LAYERS; i++) {
        int currentCycle = i ;

        String pos = positionAtA ? "A" : "B";
        int progress = map(i,0,NUMBER_OF_LAYERS , 0, 100);

        updateScreen("Moving To Position: " + pos, currentCycle, progress);
        moveToPosition(positionAtA ? POSITION_A : POSITION_B);
        updateScreen("At Position: " + pos, currentCycle, progress);
        delay(1000);

        Serial.println("Syringe Pump Starting");
        updateScreen("Disp. Sol.: " + pos, currentCycle, progress);
        dispenseVolume();
        Serial.println("Syringe Pump Finished");
        delay(1000);

        updateScreen("Spinning Substrate", currentCycle, progress);
        Serial.println("Motor Loop Starting");
        motorLoop();
        Serial.println("Motor loop finished");
        delay(1000);

        positionAtA = !positionAtA;
    }
    //updateScreen("Process Complete", NUMBER_OF_LAYERS, 100);
    delay(10000);
}
