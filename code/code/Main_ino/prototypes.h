#ifndef PROTOTYPES_H
#define PROTOTYPES_H

void motorSetup();
void motorLoop();
void syringePump_Setup();
void dispenseVolume();
void linearStage_Setup();
void homeStage();
void moveToPosition(int position);
void updateScreen(const String& status, int cycleNum);

#endif
