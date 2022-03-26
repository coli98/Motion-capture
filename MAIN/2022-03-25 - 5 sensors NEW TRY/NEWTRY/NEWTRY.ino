#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
// include the SD library:
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>


#define NAMECHEST "chest"
#define NAMEBICEP_R "upper_arm.R"
#define NAMEFOREARM_R "forearm.R"
#define NAMEBICEP_L "upper_arm.L"
#define NAMEFOREARM_L "forearm.L"
#define NAMEHAND_L "hand.L"


//Connetion id sensor with name 
typedef enum 
{
      CHEST,                                       
      BICEP_R,                                    
      FOREARM_R,                                                                           
      BICEP_L,                                      
      FOREARM_L                                                                   
} sensor_id;


#define BNO055_SAMPLERATE_DELAY_MS (0)


Adafruit_BNO055 chest = Adafruit_BNO055(-1,0x70, 7);
bool chestPresent;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
