#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 myIMU = Adafruit_BNO055();

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myIMU.begin();
delay(1000);
int8_t temp = myIMU.getTemp();
Serial.println(temp);
myIMU.setExtCrystalUse(true);
}

void loop() {
  // put your main code here, to run repeatedly:

}
