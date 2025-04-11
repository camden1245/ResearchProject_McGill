#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <Arduino.h>

void motorSetup();
void motorLoop();
void syringePump_Setup();
void dispenseVolume();
void linearStage_Setup();
void homeStage();
void moveToPosition(int position);
void updateScreen(const String& status, int cycleNum);

enum StatusMsg {
    MSG_MOVING_TO_POS,
    MSG_AT_POS,
    MSG_DISPENSING,
    MSG_SPINNING
};

void getStatusMessage(char* dest, StatusMsg msg, const char* suffix = nullptr);

#endif
