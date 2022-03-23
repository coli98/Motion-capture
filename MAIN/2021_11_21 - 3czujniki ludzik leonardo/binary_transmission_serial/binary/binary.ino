
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//#include <SD.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define TCAADDR 0x70

typedef union {
  double floatingPoint;
  byte binary[4];
} binaryFloat;
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
float StartTime = 0; //Timer 
long loopCounter = 0; //keeps track of the number of iterations
uint32_t testNumber = 0; //a 24-bit number as an example 14480912 - 00000000|11011100|11110110|00010000
byte testbuffer[3]; //buffer that stores 3x8=24 bits (3 bytes) 

double value = 123.456;

void setup() {
  
  Serial.begin(115200);
  Wire.begin();
    uint8_t ch;
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
  
  delay(1000); //wait 1 s
tcaselect(3); 
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
binaryFloat EulerX;
EulerX.floatingPoint = euler.x();
    byte incomingBytes;
//   float a = 12.34;
//   byte dataArray[4] = {
//      ((uint8_t*)&a)[0],
//      ((uint8_t*)&a)[1],
//      ((uint8_t*)&a)[2],
//      ((uint8_t*)&a)[3]
//   };
//
//   for (int x =0; x<sizeof(dataArray); x=x+1){
//  Serial.write(dataArray[x]);
//  Serial.read(incomingBytes);
//}

//Serial.write(EulerX.binary,4);

float temp = -11.7;   
byte * b = (byte *) &temp;
  Serial.write(b,4);
    if (Serial.available() > 0) {
    // Read the incoming bytes.
    incomingBytes = Serial.read();}
  Serial.print("\nIncomingbytes: "); Serial.print(incomingBytes);
//  Serial.print(F("Value uses "));
//  Serial.print(sizeof(euler.x()));
//  Serial.print(F(" bytes in Memory starting at address 0x"));
//  Serial.println((uint16_t) valuePtr, HEX);
//
//    for (size_t i = 0; i < sizeof(euler.x()); i++) {
//    Serial.print(F("Memory address 0x"));
//    Serial.print((uint16_t) (valuePtr + i), HEX);
//    Serial.print(F("= 0x"));
//    Serial.println(*(valuePtr + i), HEX);
//  }
  //Serial.println("2000000 test");
}

void loop() 
{
//  if (Serial.available() > 0) 
//  {
//    char commandCharacter = Serial.read(); //we use characters (letters) for controlling the switch-case  
//    switch (commandCharacter) //based on the command character, we decide what to do
//    { 
//      case 'b': //binary  
//            tcaselect(3); 
//            imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); 
//            testNumber = 0; //test number          
//            loopCounter = 0; //counts the iterations of the loop
//            StartTime = micros(); //starts the timer
//            while (loopCounter < 50000000) //5M points  
//            {
//            //-------------------------------------------------------------------
//            testbuffer[0] = euler.x() & 255; //first 8 bits - bitwise AND keeps the first 8 digits
//            //Serial.print("Buffer 0: ");
//            //Serial.println(testbuffer[0]); //print the first part of the output
//            //------------------------------------------------
//            testbuffer[1] = (euler.x()>>8) & 255; //8-15 bits  
//            //shifts the 8-15 bits to the first 8 places (>>8) and keeps only those (&255)
//            //Serial.print("Buffer 1: ");
//            //Serial.println(testbuffer[1]); //print the second part of the output
//            //--------------------------------------------------
//            testbuffer[2] = (euler.x()>>16) & 255; //16-23 bits
//            //shifts the 16-23 bits to the first 8 places (>>16) and keeps only those (&255)
//            //Serial.print("Buffer 2: ");
//            //Serial.println(testbuffer[2]); //print the third part of the output
//            //-------------------------------------------
//            Serial.write(testbuffer, sizeof(testbuffer)); //dump the buffer to the serial port (24 bit number in 3 bytes)
//            loopCounter++; //Increase the value of the counter (+1)
//            testNumber = loopCounter; //this here might be inefficient, we could directly work with a single variable
//            
//              if(micros() - StartTime >= 5000000) //5 s; If the timer ends before 1M points are transfered, we jump out
//              {              
//                break; //exit the whole thing              
//              }        
//            }            
//            break;
//      //-----------------------------------------------------------------------------------------------------------------
//      case 'd': //decimal      
//          loopCounter = 0; //counts the iterations of the loop
//          StartTime = micros(); //starts the timer
//          while (loopCounter < 1000000) //1M points  
//          {          
//          Serial.println(loopCounter); //dump the number to the serial port with a linebreak (one at a time)
//          loopCounter++; //Increase the value of the counter  
//          
//            if(micros() - StartTime >= 5000000) //5 s; If the timer ends before 1M points are transfered, we jump out
//            {
//              Serial.println("Time is over");
//              break; //exit the whole thing              
//            }        
//          }            
//          break;
//      }    
//  }
}
