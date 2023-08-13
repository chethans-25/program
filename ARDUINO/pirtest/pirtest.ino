
int pirSensor = 8;
int led = 13;
int buzzer = 11;
int count;
void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  count=0;
}                

void loop() {
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1){
    digitalWrite(led , 1 ); //
    tone(buzzer,900,1000);
  }
  else
    digitalWrite(led , 0 ); //
  }
