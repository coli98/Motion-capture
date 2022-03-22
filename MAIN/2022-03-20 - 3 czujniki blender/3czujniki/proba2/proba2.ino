#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

String CommandFromPC;
bool flagaSTART = 0;
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
    pinMode(50, INPUT_PULLUP); //Przycisk jako wejście
    Serial.begin(115200);
   // Serial.println(""); Serial.println("Orientation Sensor Test"); Serial.println("");
  
    Wire.begin();
  
    uint8_t ch;
  // Petla sprawdza czy w ogole sa jakies urzadzenia
    for (ch=3; ch<5; ch++)  // multiple I2C devices
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
  
  }

void loop(void)
  {
  if (digitalRead(50) == LOW){
    flagaSTART = 1;
    delay(3000);
    Serial.println("BEGIN");
  }

    while (flagaSTART==1){
    delay(100);
    uint8_t ch;
  
    // if(Serial.available() > 0)
          //  {
            //  CommandFromPC = Serial.readStringUntil('\n');
          
            //if (CommandFromPC == "g")
            //{            
                for (ch=3; ch<5; ch++)  // multiple I2C devices
                  {
                      tcaselect(ch);
                  
                      /* Get a new sensor event */
                      sensors_event_t event;
                      bno.getEvent(&event);
                      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
                      Serial.print(euler.x());
                      Serial.print(" ");
                      Serial.print(euler.y());
                      Serial.print(" ");
                      Serial.print(euler.z());
                      Serial.print(" ");

                  
                    }                                             
                Serial.print("\n");
                delay(500);
               //}
             //}
    if (digitalRead(50) == LOW){
      flagaSTART = 0;
      Serial.println("STOP");
      delay(5000);
          }
    }
  }
