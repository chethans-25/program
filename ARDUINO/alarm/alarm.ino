
int pirSensor = 8;
int buzzer = 11;
void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(buzzer, OUTPUT);
}                

void loop() {
  int i=0;
  int sensorValue = digitalRead(pirSensor);
  if(sensorValue==1)
  for (i=0;i<5;i++){
    tone(buzzer,900,500);
    delay(500);
    tone(buzzer,1000,500);
    delay(500);
    }
}
    
    
