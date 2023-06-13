#include <Bounce2.h>

bool prev = false;

const uint8_t BOOT_PIN = 0;
const uint8_t RELAY_PIN = 10;

Bounce2::Button button = Bounce2::Button();

void setup() {
  button.attach(BOOT_PIN, INPUT_PULLUP);
  button.interval(25); // milliseconds
  button.setPressedState(LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(115200);
  delay(5000);

  Serial.println("MiniSSO Tester Relay Test");
  Serial.println("Press 'Boot' button to active relay");
}

void loop() {
  button.update();

  if (button.isPressed()) {
    if (prev != true) {
      prev = true;
      Serial.println("'Boot' button pressed");
      digitalWrite(RELAY_PIN, HIGH);
    }
  } else {
    if (prev != false) {
      prev = false;
      Serial.println("'Boot' button not pressed");
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}
