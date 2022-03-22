#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//#include <SD.h>
#include "SdFat.h"
#include <SPI.h>
SdFat SD; 

File myFile;
unsigned long CurrentTime = 0;
unsigned long BlockTime = 0; 
String CommandFromPC;

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define TCAADDR 0x70

/* select I2C channel using TCA9548A multiplexer */
void tcaselect(uint8_t channel)
{
//  Serial.print("I2C Channel: ");  Serial.print(channel); Serial.print(F(" "));
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x29);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);

  delay(500);
}

void setup(void)
{
  Serial.begin(115200);
//  Serial.println(""); Serial.println("Orientation Sensor Test"); Serial.println("");

  Wire.begin();

  uint8_t ch;
// Petla sprawdza czy w ogole sa jakies urzadzenia
  for (ch=3; ch<8; ch++)  // multiple I2C devices
  {
    tcaselect(ch);

    /* Initialise the sensor */
    if(!bno.begin())
    {
      /* There was a problem detecting the BNO055 ... check your connections */
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      while(1);
    }
  }
  if (!SD.begin(10)) {
      Serial.println("initialization failed!");
      while (1);
    }
    
    
  delay(1000);
// Petla wypisuje informacje o sensorach 
//  for (ch=2; ch<4; ch++)  // multiple I2C devices
//  {
//    tcaselect(ch);
//
//    /* Display some basic information on this sensor */
//    displaySensorDetails();
//  }

  delay(100);
  //uint8_t ch;

  myFile = SD.open("test.txt", FILE_WRITE);

          for(int i=0; i<200; i++){
              for (ch=3; ch<8; ch++)  // multiple I2C devices
                {
                    CurrentTime = micros();                 
                    tcaselect(ch);
                
                    /* Get a new sensor event */
//                    sensors_event_t event;
//                    bno.getEvent(&event);
                    
                    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
                   
                  //bno.getCalibration(&sys, &gyro, &accel, &mag);
                    myFile.print(euler.x());
                    myFile.print(" ");
                    myFile.print(euler.y());
                    myFile.print(" ");
                    myFile.print(euler.z());
                    myFile.print(" ");
                    myFile.print(CurrentTime);
                    myFile.print(" ");                                           
//                    myFile.print(event.orientation.x);
//                    myFile.print(" ");
//                    myFile.print(event.orientation.y);
//                    myFile.print(" ");
//                    myFile.print(event.orientation.z);
//                    myFile.print(" ");
//                    myFile.print(CurrentTime);
//                    myFile.print(" ");   
                  }  
              BlockTime = micros();
              myFile.print(BlockTime);                                               
              myFile.print("\n");
             //}
              
          }
           //}
    myFile.close();
    Serial.print("I have ended file trasfer!"); 

}

void loop(void)
{

}
