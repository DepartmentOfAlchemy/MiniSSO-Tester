#include <Bounce2.h>
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

#define INTERVAL_DELAY 500

#define C7 2093
#define D7 2349
#define E7 2637
#define F7 2794
#define G7 3134
#define A7 3520
#define B7 3951
#define C8 4186
#define D8 4699
#define E8 5274
#define F8 5588
#define G8 6272
#define A8 7040
#define B8 7902

bool prev = false;
bool UNIT_TEST_TOGGLE = false;

// TODO: delete BOOT once tester is tested
static const uint8_t BOOT_PIN = 0;
static const uint8_t PIEZO_PIN = A0;
static uint8_t RELAY_PIN = 10;

// MiniSSO pins
static const uint8_t INPUT_PIN = 13;
uint8_t OUTPUT_PINS[] = {12, 11};

// TODO: Delete BOOT once tester is tested
Bounce2::Button button = Bounce2::Button();

Bounce2::Button input = Bounce2::Button();

Waveshare_LCD1602_RGB lcd(16,2);  //16 characters and 2 lines

void successTone() {
  tone(PIEZO_PIN, C8); // C8
  delay(200);
  tone(PIEZO_PIN, B7); // E8
  delay(100);
  tone(PIEZO_PIN, E8); // G8
  delay(300);
  noTone(PIEZO_PIN);
}

void failTone() {
  tone(PIEZO_PIN, C8);
  delay(300);
  noTone(PIEZO_PIN);
  tone(PIEZO_PIN, A7);
  delay(1000);
  noTone(PIEZO_PIN);
}

void startup() {
  lcd.clear();
  lcd.setColorWhite();
  lcd.setCursor(0,0);
  lcd.send_string("Department of");
  lcd.setCursor(0,1);
  lcd.send_string("Alchemy");
  Serial.println("Department of Alchemy");
  Serial.println();

  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.send_string("MiniSSO Tester");
  Serial.println("MiniSSO Tester");
  Serial.println();

  delay(2000);
}

void waitingToTest() {
  // reset to known state
  digitalWrite(RELAY_PIN, LOW); // switch to sense output 1

  // set both outputs low, input should not be 'pressed'
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 0);

  lcd.clear();
  lcd.setColorWhite();
  lcd.setCursor(0,0);
  lcd.send_string("Press boot on");
  lcd.setCursor(0,1);
  lcd.send_string("controller");
  Serial.println("Press boot on controller to test.");
  Serial.println();
}

void test() {
  lcd.clear();
  lcd.setColorWhite();
  lcd.setCursor(0,0);
  lcd.send_string("Testing...");
  Serial.println("Testing...");

  // TODO: similuated test. replace with real test.
  /*
  if (UNIT_TEST_TOGGLE) {
    lcd.setRGB(0,255,0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.send_string("Passed");
    successTone();
  } else {
    lcd.setRGB(255,0,0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.send_string("FAILED");
    failTone();
  }
  UNIT_TEST_TOGGLE = !UNIT_TEST_TOGGLE;
  */
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.send_string("Press button on");
  lcd.setCursor(0, 1);
  lcd.send_string("MiniSSO");
  Serial.println("Press button on MiniSSO");
  while (digitalRead(INPUT_PIN) == HIGH) {
    // not pressed
  }

  //
  // test output 1
  //
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.send_string("Testing output 1");
  Serial.println("Testing output 1");
  digitalWrite(RELAY_PIN, LOW); // switch to sense output 1

  // set both outputs low, input should not be 'pressed'
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 0);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == LOW) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 OFF, output 2 OFF, but input was ON");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 low, output 2 high, input should not be 'pressed'
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 255);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == LOW) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 OFF, output 2 ON, but input was ON");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 high, output 2 low, input should be 'pressed'
  analogWrite(OUTPUT_PINS[0], 255);
  analogWrite(OUTPUT_PINS[1], 0);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == HIGH) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 ON, output 2 OFF, but input was OFF");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 high, output 2 high, input should be 'pressed'
  analogWrite(OUTPUT_PINS[0], 255);
  analogWrite(OUTPUT_PINS[1], 255);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == HIGH) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 ON, output 2 ON, but input was OFF");
    failTone();
    delay(2000);
    return;
  }

  //
  // test output 2
  //
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.send_string("Testing output 2");
  Serial.println("Testing output 2");
  digitalWrite(RELAY_PIN, HIGH); // switch to sense output 2

  // set both outputs low, input should not be 'pressed'
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 0);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == LOW) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 OFF, output 2 OFF, but input was ON");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 low, output 2 high, input should be 'pressed'
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 255);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == HIGH) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 OFF, output 2 ON, but input was OFF");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 high, output 2 low, input should no be 'pressed'
  analogWrite(OUTPUT_PINS[0], 255);
  analogWrite(OUTPUT_PINS[1], 0);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == LOW) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 ON, output 2 OFF, but input was ON");
    failTone();
    delay(2000);
    return;
  }

  // set output 1 high, output 2 high, input should be 'pressed'
  analogWrite(OUTPUT_PINS[0], 255);
  analogWrite(OUTPUT_PINS[1], 255);

  delay(INTERVAL_DELAY);

  //input.update();
  if (digitalRead(INPUT_PIN) == HIGH) {
    lcd.setRGB(255,0,0);
    lcd.setCursor(0,1);
    lcd.send_string("FAILED!");
    Serial.println("FAILED! Output 1 ON, output 2 ON, but input was OFF");
    failTone();
    delay(2000);
    return;
  }

  // passed!
  // turn outputs off
  analogWrite(OUTPUT_PINS[0], 0);
  analogWrite(OUTPUT_PINS[1], 0);
  // reset to sense output 1
  digitalWrite(RELAY_PIN, LOW);

  lcd.setRGB(0,255,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.send_string("Passed");
  Serial.println("Passed");
  successTone();
  delay(2000);
}

void setup() {
  // TODO: delete BOOT when 
  button.attach(BOOT_PIN, INPUT_PULLUP);
  button.interval(25); // milliseconds
  button.setPressedState(LOW);

  /*
  input.attach(INPUT_PIN, INPUT);
  input.interval(25); // milliseconds
  input.setPressedState(LOW);
  */
  pinMode(INPUT_PIN, INPUT);

  pinMode(OUTPUT_PINS[0], OUTPUT);
  pinMode(OUTPUT_PINS[1], OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  lcd.init();

  Serial.begin(115200);
  delay(3000);

  startup();
  waitingToTest();
}

void loop() {
  button.update();
  input.update();

  if (button.isPressed()) {
//  if (input.isPressed()) {
    if (prev != true) {
      prev = true;
      Serial.println("'Boot' button pressed");
      //digitalWrite(RELAY_PIN, HIGH);

      test();
      waitingToTest();
    }
  } else {
    if (prev != false) {
      prev = false;
      Serial.println("'Boot' button not pressed");
      //digitalWrite(RELAY_PIN, LOW);
    }
  }
}
