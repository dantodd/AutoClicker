#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     7 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


Encoder myEnc(5, 6);

int oldPosition;
int newPosition;
int initialCPS = 50;
byte cps = initialCPS; //this prevents negative numbers and limits to 255 clicks per second

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  pinMode(4, INPUT_PULLUP); // autoclick initiate
  pinMode(17, INPUT_PULLUP); // rotary encoder button (set)

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  // Iniitial display setup so it isn't blank until CPS is changed
  display.clearDisplay();
  display.setTextSize(4); // Draw 4X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(52,3);
  display.println(cps);
  display.setTextSize(2); // Draw 2x-scale text
  display.setCursor(5,10);
  display.println("CPS");
  display.display();      // Show initial text

}

void loop() {
  newPosition = myEnc.read();

  
  if (newPosition != oldPosition) {

    oldPosition = newPosition;
    cps = newPosition + initialCPS;
    display.clearDisplay();
    display.setTextSize(4); // Draw 4X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(52,3);
    display.println(cps);
    display.setTextSize(2); // Draw 2x-scale text
    display.setCursor(5,10);
    display.println("CPS");
    display.display();      // Show initial text

  }
  if (digitalRead(4) == LOW) {
    Mouse.click();
    delay(1000/cps);
  }
  
}
