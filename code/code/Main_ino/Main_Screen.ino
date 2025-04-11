#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>
#include "prototypes.h" // Required for StatusMsg enum and function prototype

/*
Pin Configurations: 
VCC -> 5V
GND -> GND
SDA -> 11 (MOSI)
SCL -> 13 (SCK)
RES -> 6
CS  -> 7
DC  -> 8
*/


// OLED Pin Definitions
#define OLED_CS     7
#define OLED_DC     8
#define OLED_RESET  6

// Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Optional: cycle counter
int currentCycle = 0;

/*
PROGMEM status messages

These status strings are stored in flash memory instead of RAM to reduce memory usage.
Only one message is loaded into RAM at a time using the `getStatusMessage` function.
*/
const char msg_moving_to_pos[] PROGMEM = "Moving To Pos: ";
const char msg_at_pos[]        PROGMEM = "At Position: ";
const char msg_dispensing[]    PROGMEM = "Dispensing Solution: ";
const char msg_spinning[]      PROGMEM = "Spinning Substrate";

// Array of pointers to each string in PROGMEM
const char* const statusMessages[] PROGMEM = {
  msg_moving_to_pos,
  msg_at_pos,
  msg_dispensing,
  msg_spinning
};

/*
Copies a flash-stored status message (based on enum index) into a RAM buffer.
An optional suffix can be appended (e.g., "A" or "B" for position).

    Parameters:
        dest   - char buffer in RAM to receive the message
        msg    - StatusMsg enum value
        suffix - optional C-style string to append

    Used in: loop() to assemble the full status message for the OLED screen.
*/
void getStatusMessage(char* dest, StatusMsg msg, const char* suffix = nullptr) {
    strcpy_P(dest, (PGM_P)pgm_read_word(&(statusMessages[msg])));
    if (suffix) {
        strcat(dest, suffix);
    }
}


void screen_setup() {
    /*
    Initializes the OLED screen for use.

    Called in: setup()

    - Begins SPI communication
    - Initializes the OLED driver
    - Displays startup message
    */

    SPI.begin();
    
    if (!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true); // hang
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Spin Coater Ready");
    display.display();
}


void updateScreen(const char* status, int cycleNum, int progress) {

        /*
        Updates the OLED screen with current status

         Parameters:
         status   - char* status string (must be pre-assembled in RAM)
         cycleNum - current cycle number
         progress - % progress (0-100)

         Called repeatedly during main loop to reflect current operation.
         Displays:
            - System name
            - Cycle count
            - Status message
            - Progress bar and percent
        */
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Header
    display.setCursor(0, 0);
    display.println("Spin Coater");

    // Cycle count
    display.setCursor(0, 12);
    display.print("Cycle: ");
    display.print(cycleNum);
    display.print("/");
    display.print(NUMBER_OF_LAYERS);

    // Status
    display.setCursor(0, 24);
    display.print("Status:");
    display.setCursor(0, 34);
    display.println(status);

    // Progress bar
    int barWidth = map(progress, 0, 100, 0, SCREEN_WIDTH);
    display.drawRect(0, 50, SCREEN_WIDTH, 10, SSD1306_WHITE);
    display.fillRect(0, 50, barWidth, 10, SSD1306_WHITE);

    // Percentage text
    display.setCursor(SCREEN_WIDTH - 25, 51);
    display.print(progress);
    display.print("%");

    display.display();
}
