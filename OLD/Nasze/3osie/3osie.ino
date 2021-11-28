String CommandFromPC;
const int trigPin = 9;
const int echoPin = 8;
float duration, distance;

void setup() {
    CommandFromPC = "";
      Serial.begin(115200);
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
}

void loop() {

  if(Serial.available() > 0)
  {
    CommandFromPC = Serial.readStringUntil('\n');

    if (CommandFromPC == "Hello Arduino"){
    Serial.println("co jest kurwa? PROBLEM?!");
    }

  else if (CommandFromPC == "Get distance"){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    Serial.println(distance);    
    }
    
   }
  
  }
