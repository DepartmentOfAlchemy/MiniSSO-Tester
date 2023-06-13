
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"


Waveshare_LCD1602_RGB lcd(16,2);  //16 characters and 2 lines of show
int r,g,b,t=0;
#define DELAY 20
void setup() {
    // initialize
    lcd.init();
    
    lcd.setCursor(0,0);
    lcd.send_string("Department of");
    lcd.setCursor(0,1);
    lcd.send_string("Alchemy");
}

void loop() {
  r = 255;
  g = 0;
  b = 0;

  for (int i = 0; i <= 255; i++) {
    g = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }

  for (int i = 255; i >= 0; i--) {
    r = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }

  for (int i = 0; i <= 255; i++) {
    b = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }

  for (int i = 255; i >= 0; i--) {
    g = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }

  for (int i = 0; i <= 255; i++) {
    r = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }

  for (int i = 255; i >= 0; i--) {
    b = i;
    lcd.setRGB(r, g, b);
    delay(DELAY);
  }
}
