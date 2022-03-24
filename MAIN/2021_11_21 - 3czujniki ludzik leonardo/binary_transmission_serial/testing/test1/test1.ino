typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;


String CommandFromPC;


void setup() {
  // put your setup code here, to run once:
//  binaryFloat hi;
 // hi.floatingPoint = -11.7;
  Serial.begin(115200);
//  Serial.write(hi.binary,4);
}

void loop() {
  // put your setup code here, to run once:
 
 uint8_t data[6] = {1, 20, 1, 1, 0, 0};
 binaryFloat hi;
 hi.floatingPoint = -11.7;


  if(Serial.available() > 0)
            {
              CommandFromPC = Serial.readStringUntil('\n');
          
            if (CommandFromPC == "g"){
            // // Serial.begin(115200);

                  Serial.write(data, 6);
                  Serial.print('\n');
                                      }
            }
}
