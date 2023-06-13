#include <Wire.h>
#include "LCD_C0220BiZ.h"
#include "ST7036.h"

ST7036 lcd = ST7036(2, 20, 0x78);

// index for pin for the particular color
#define RED 0
#define GREEN 1
#define BLUE 2

// pins used for the LCD LED backlight, R-G-B
const uint8_t BACKLIGHT[] = { 9, 6, 5 };

void setBacklight(uint8_t red, uint8_t green, uint8_t blue) {
  // common annode
  uint8_t scaledBrightness;

  scaledBrightness = 255 - red;
  Serial.print("Setting pin RED ");
  Serial.print(BACKLIGHT[RED]);
  Serial.print(" to the value: ");
  Serial.println(scaledBrightness);
  analogWrite(BACKLIGHT[RED], red);

  scaledBrightness = 255 - green;
  Serial.print("Setting pin GREEN ");
  Serial.print(BACKLIGHT[GREEN]);
  Serial.print(" to the value: ");
  Serial.println(scaledBrightness);
  analogWrite(BACKLIGHT[GREEN], scaledBrightness);

  scaledBrightness = 255 - blue;
  Serial.print("Setting pin BLUE ");
  Serial.print(BACKLIGHT[BLUE]);
  Serial.print(" to the value: ");
  Serial.println(scaledBrightness);
  analogWrite(BACKLIGHT[BLUE], scaledBrightness);
}

void setup() {
  uint8_t status;
  Serial.begin(115200);

  delay(5000);

  Serial.println(F("\nStarting MiniSSO Tester Display Test"));
  Serial.println();

  Serial.println("Initializing display...");

  // setup the backlight pins
  pinMode(BACKLIGHT[RED], OUTPUT);
  pinMode(BACKLIGHT[GREEN], OUTPUT);
  pinMode(BACKLIGHT[BLUE], OUTPUT);

  lcd.init();
  Serial.print("lcd.init status: ");
  Serial.println(lcd.status());
  lcd.setDelay(10, 10);
  Serial.print("lcd.setDelay status: ");
  Serial.println(lcd.status());
  delay(50);
  lcd.clear();
  Serial.print("lcd.clear status: ");
  Serial.println(lcd.status());
  delay(50);
  lcd.setCursor(0, 2);
  Serial.print("lcd.setCursor status: ");
  Serial.println(lcd.status());

  Serial.println("Displaying 'Hello, World!' message...");

  setBacklight(0, 0, 255);

  //lcd.print("Hello,");
  lcd.write('H');
  Serial.print("lcd.write('H') status: ");
  Serial.println(lcd.status());

//  lcd.write('e');
//  lcd.write('l');
//  lcd.write('l');
//  lcd.write('o');
//  lcd.write(',');
  Serial.println("Displayed 'Hello,'");
  lcd.setCursor(1, 2);
  Serial.print("lcd.setCursor(1, 2) status: ");
  Serial.println(lcd.status());
  Serial.println("Set cursor to 1, 2");
  //lcd.print("World!");
//  lcd.write('W');
//  lcd.write('o');
//  lcd.write('r');
//  lcd.write('l');
//  lcd.write('d');
//  lcd.write('!');
  Serial.println("Displayed 'World!'");
}

void loop() {
  // loop through the 3 backlight colors
  Serial.println("Red backlight");
  setBacklight(255, 0, 0);
  delay(2000);
  Serial.println("Green backlight");
  setBacklight(0, 255, 0);
  delay(2000);
  Serial.println("Blue backlight");
  setBacklight(0, 0, 255);
  delay(2000);
}
