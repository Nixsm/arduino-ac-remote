#include "komeco.h"

KomecoController komeco;

void setup()
{
  pinMode(2, OUTPUT);
  komeco.setup();
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  Serial.printf("Setting temperature to 21\n");
    // digitalWrite(2, LOW);
    komeco.setTemperatureTo(21);
    // digitalWrite(2, LOW);
    delay(10000);
    Serial.printf("Turning off...\n");
    komeco.turnOff();
    // digitalWrite(2, LOW);
    delay(10000);
  // int temp = Serial.parseInt();
  // Serial.printf("temp: " + temp);
//   if (temp == 0) {
//     komeco.turnOff();
//   } else {
//     komeco.setTemperatureTo(temp);
//   }
}
