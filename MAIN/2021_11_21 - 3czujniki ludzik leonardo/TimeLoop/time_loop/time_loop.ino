
unsigned long aktualnyCzas = 0;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //Pobierz liczbe milisekund od startu
  aktualnyCzas = micros();
  Serial.println(aktualnyCzas);


  
}
