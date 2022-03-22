#include <Wire.h>

void setup() {

  pinMode(50, INPUT_PULLUP); //Przycisk jako wejście
  Serial.begin(115200);
}
 
void loop()
{
  if (digitalRead(50) == LOW) { //Jeśli przycisk wciśnięty
  Serial.println("przycisk");
  delay(1000);
  }
}
