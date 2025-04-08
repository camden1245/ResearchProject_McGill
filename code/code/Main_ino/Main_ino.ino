// Main.cpp
//#include "Main_Settings_ino.ino"
//#include "Main_LinearStage_ino.ino"
//#include "Main_BLDC_ino.ino"
//#include "Main_SyringePump_ino.ino"
#include "Main_Settings.h"
#include "prototypes.h"

void setup() {
	/*
	Initialize all components
	*/
	
    Serial.begin(9600);
    screen_setup();
    updateScreen("System Initialized");

    linearStage_Setup();
    //motorSetup();
    syringePump_Setup();
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
    static bool positionAtA = true;
    
    for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
        int currentCycle = i + 1;

        String pos = positionAtA ? "A" : "B";
        int progress = map(i,0,NUMBER_OF_LAYERS - 1, 0, 100);

        updateScreen("Moving To Position: " + pos, currentCycle, progress);
        moveToPosition(positionAtA ? POSITION_A : POSITION_B);
        updateScreen("At Position: " + pos, currentCycle, progress);
        delay(1000);

        updateScreen("Dispensing Solution: " + pos, currentCycle), progress;
        dispenseVolume();
        delay(1000);

        updateScreen("Spinning Substrate", currentCycle, progress)
        //motorLoop();
        delay(1000);

        positionAtA = !positionAtA;
    }
    updateScreen("Process Complete", NUMBER_OF_LAYERS, 100)
    delay(10000);
}
