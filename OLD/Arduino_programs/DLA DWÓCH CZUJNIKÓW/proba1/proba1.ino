#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


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
//  Serial.println("------------------------------------");
//  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
//  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
//  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
//  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
//  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
//  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
//  Serial.println("------------------------------------");
//  Serial.println("");
  delay(500);
}

void setup(void)
{
  Serial.begin(115200);
//  Serial.println(""); Serial.println("Orientation Sensor Test"); Serial.println("");

  Wire.begin();

  uint8_t ch;
// Petla sprawdza czy w ogole sa jakies urzadzenia
  for (ch=2; ch<3; ch++)  // multiple I2C devices
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

  delay(1000);
// Petla wypisuje informacje o sensorach 
//  for (ch=2; ch<4; ch++)  // multiple I2C devices
//  {
//    tcaselect(ch);
//
//    /* Display some basic information on this sensor */
//    displaySensorDetails();
//  }
}

void loop(void)
{
  delay(100);
  uint8_t ch;




   if(Serial.available() > 0)
          {
            CommandFromPC = Serial.readStringUntil('\n');
        
          if (CommandFromPC == "Get distance")
          {
              for (ch=2; ch<4; ch++)  // multiple I2C devices
                {
                    tcaselect(ch);
                
                    /* Get a new sensor event */
                    sensors_event_t event;
                    bno.getEvent(&event);
                
                    imu::Quaternion q = bno.getQuat();
                    float temp = q.x();  q.x() = q.y();  q.y() = temp;  q.z() = -q.z();  // fly.c convention
                    q.normalize();
                    #if 0  // use broken BNO055 euler
                
                    /* The processing sketch expects data as roll, pitch, heading */
              //      Serial.print(F("Orientation: "));
              //      Serial.print( event.orientation.x);  // heading
              //      Serial.print(F(" "));
              //      Serial.print(-event.orientation.y);  // roll
              //      Serial.print(F(" "));
              //      Serial.print(-event.orientation.z);  // pitch
              //      Serial.println(F(""));
                  #else
                    /* Convert quaternion to Euler, because BNO055 Euler data is broken */
                    imu::Vector<3> euler;
                    /* Adafruit's confusing x,y,z names are actually axis Z,Y,X rotations heading,roll,pitch */
                    euler.x() = 180/M_PI * atan2(q.w()*q.z() + q.x()*q.y(), 0.5 - q.y()*q.y() - q.z()*q.z());  // heading
                    euler.y() = 180/M_PI * atan2(q.w()*q.x() + q.y()*q.z(), 0.5 - q.x()*q.x() - q.y()*q.y());  // roll
                    euler.z() = 180/M_PI * asin(2 * (q.w()*q.y() - q.x()*q.z()));  // pitch
              //      Serial.print(F("Euler: "));
                  //*****************************************************
              
              
                  
             
              
              
              //Serial.println(F(""));
                  #endif
              
                  /* send quaternion */
                  
              //    Serial.print(F("Quaternion: "));
              //    Serial.print(q.w(), 4);
              //    Serial.print(F(" "));
              //    Serial.print(q.x(), 4);
              //    Serial.print(F(" "));
              //    Serial.print(q.y(), 4);
              //    Serial.print(F(" "));
              //    Serial.print(q.z(), 4);
              //    Serial.print(F(" ")); 
              
              // niepotrzebne daje nowa linie
              //    Serial.println(F("")
              
              
                  /* Also send calibration data for each sensor. */
                  uint8_t sys, gyro, accel, mag = 0;
                  bno.getCalibration(&sys, &gyro, &accel, &mag);
              //    Serial.print(F("Calibration: "));
              //    Serial.print(sys, DEC);
              //    Serial.print(F(" "));
              //    Serial.print(gyro, DEC);
              //    Serial.print(F(" "));
              //    Serial.print(accel, DEC);
              //    Serial.print(F(" "));
              //    Serial.println(mag, DEC);
                                                                
                    Serial.print(euler.x());Serial.print(" "); //Serial.println(F(""));  // heading, nose-right is positive, z-axis points up
      
//                   Serial.print(euler.y()); Serial.println(F("")); // roll, rightwing-up is positive, y-axis points forward
//    
//                   Serial.print(euler.z());Serial.println(F(""));  // pitch, nose-down is positive, x-axis points right

//                Serial.print(" "); 
                  }
                                                              
               Serial.println((""));




             }
            
           }
        


  
}
