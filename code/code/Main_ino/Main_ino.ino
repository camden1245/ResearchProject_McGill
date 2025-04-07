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
        moveToPosition(positionAtA ? POSITION_A : POSITION_B);
        delay(1000);
        dispenseVolume();
        delay(1000);
        //motorLoop();
        delay(1000);
        positionAtA = !positionAtA;
    }
}
