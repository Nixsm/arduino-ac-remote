#include "komeco.h"

#define ESP8266 0

KomecoController komeco;

void setup()
{
  pinMode(2, OUTPUT);
  komeco.setup();
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  Serial.println("Setting sleep mode to true");
  komeco.setSleepModeTo(true);
  delay(20000);
  Serial.print("Setting temperature to 25\n");
  komeco.setTemperatureTo(21);
  delay(10000);
  Serial.print("Setting Speed to Auto\n");
  komeco.setSpeedTo(Auto);
  delay(10000);
  Serial.print("Turning off...\n");
  komeco.turnOff();
  delay(10000);
}
