//room automation code
int pirSensor = 8;
int led = 13;
int buzzer = 11;
int count;
void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(led, OUTPUT);
  count=0;
}                

void loop() {
  int sensorValue = digitalRead(pirSensor);
  if(sensorValue==1) count=count+1;
  if (count%2==1){
    digitalWrite(led , 1 ); 
  }
  else
    digitalWrite(led , 0 ); //
  }
