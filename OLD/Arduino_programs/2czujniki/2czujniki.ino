#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
#define TCAADDR 0x70

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x29);

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  Wire.begin();


  
  /* Initialise the sensor */
//  tcaselect(2);
//  delay(1000);
//  bno.begin();
//  if (!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//   
//    
//    while (1);
//  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{

  tcaselect(2);
  
  bno.begin();
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, zesralo sie");
   
  
    while (1);
    }

  
                      // Possible vector values can be:
                      // - VECTOR_ACCELEROMETER - m/s^2
                      // - VECTOR_MAGNETOMETER  - uT
                      // - VECTOR_GYROSCOPE     - rad/s
                      // - VECTOR_EULER         - degrees
                      // - VECTOR_LINEARACCEL   - m/s^2
                      // - VECTOR_GRAVITY       - m/s^2
                      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
                    
                      /* Display the floating point data */
                      Serial.print("X: ");
                      Serial.print(euler.x());
                      Serial.print(" Y: ");
                      Serial.print(euler.y());
                      Serial.print(" Z: ");
                      Serial.print(euler.z());
                      Serial.print("\t\t");
                    
                      /*
                        // Quaternion data
                        imu::Quaternion quat = bno.getQuat();
                        Serial.print("qW: ");
                        Serial.print(quat.w(), 4);
                        Serial.print(" qX: ");
                        Serial.print(quat.x(), 4);
                        Serial.print(" qY: ");
                        Serial.print(quat.y(), 4);
                        Serial.print(" qZ: ");
                        Serial.print(quat.z(), 4);
                        Serial.print("\t\t");
                      */
                    
                      /* Display calibration status for each sensor. */
                      uint8_t system, gyro, accel, mag = 0;
                      bno.getCalibration(&system, &gyro, &accel, &mag);
                      Serial.print("CALIBRATION: Sys=");
                      Serial.print(system, DEC);
                      Serial.print(" Gyro=");
                      Serial.print(gyro, DEC);
                      Serial.print(" Accel=");
                      Serial.print(accel, DEC);
                      Serial.print(" Mag=");
                      Serial.println(mag, DEC);
                    
                      delay(BNO055_SAMPLERATE_DELAY_MS);
}

void tcaselect(uint8_t i)
{
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
