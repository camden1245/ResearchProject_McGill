#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
// Pins
#define OLED_CS     7
#define OLED_DC     8
#define OLED_RESET  6  // Note: Fixed typo from OLED_RES to OLED_RESET to match library

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Optional: cycle counter
int currentCycle = 0;

void screen_setup() {
    // Initialize SPI (if not already done elsewhere)
    SPI.begin();
    
    // OLED setup
    if (!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        // Print more debug info
        Serial.println(F("Check wiring:"));
        Serial.print(F("CS: ")); Serial.println(OLED_CS);
        Serial.print(F("DC: ")); Serial.println(OLED_DC);
        Serial.print(F("RESET: ")); Serial.println(OLED_RESET);
        while (true); // hang forever
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Spin Coater Ready");
    display.display();
}

void updateScreen(const String& status, int cycleNum, int progress) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Header
    display.setCursor(0, 0);
    display.println("Spin Coater");

    // Cycle number
    display.setCursor(0, 12);
    display.print("Cycle: ");
    display.print(cycleNum);
    display.print("/");
    display.print(NUMBER_OF_LAYERS);

    // Status message (split across two lines if needed)
    display.setCursor(0, 24);
    display.print("Status:");
    display.setCursor(0, 34);
    display.println(status); // This will automatically wrap if too long

    // Draw Progress Bar (bottom of the screen)
    int barWidth = map(progress, 0, 100, 0, SCREEN_WIDTH);
    display.drawRect(0, 50, SCREEN_WIDTH, 10, SSD1306_WHITE);
    display.fillRect(0, 50, barWidth, 10, SSD1306_WHITE);

    // Display percentage
    display.setCursor(SCREEN_WIDTH - 25, 51);
    display.print(progress);
    display.print("%");

    display.display();
}