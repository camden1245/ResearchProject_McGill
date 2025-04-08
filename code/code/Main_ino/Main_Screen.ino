#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


/*
Pin Configurations: 
VCC -> 5V
GND -> GND
SDA -> D
SCL -> D
RES -> D
CS  -> D
*/
// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Optional: cycle counter
int currentCycle = 0;

void screen_setup() {
    
    // OLED setup
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
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

    display.setCursor(0, 0);
    display.println("Spin Coater");

    display.setCursor(0, 20);
    display.print("Cycle #: ");
    display.println(cycleNum);

    display.setCursor(0, 40);
    display.print("Status:");
    display.setCursor(0, 50);
    display.println(status);

    // Draw Progress Bar (bottom of the screen)
    int barWidth = map(progress, 0, 100, 0, SCREEN_WIDTH); // Map progress to screen width
    display.drawRect(0, 55, SCREEN_WIDTH, 10, SSD1306_WHITE); // Outline of progress bar
    display.fillRect(0, 55, barWidth, 10, SSD1306_WHITE); // Fill progress

    // Display percentage next to progress bar
    display.setCursor(SCREEN_WIDTH - 30, 55);
    display.print(progress);
    display.print("%");

    display.display();
}