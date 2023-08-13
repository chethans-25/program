int trigerpin=7;
int echopin=8;
int traveltime;
float distance;
int buzpin=12;

void setup()
 {  // put your setup code here, to run once:
pinMode(trigerpin,OUTPUT);
pinMode(echopin,INPUT);
pinMode(buzpin,OUTPUT);
Serial.begin(9600);}

void loop()
{  // put your main code here, to run repeatedly:  
digitalWrite(trigerpin,LOW);
delayMicroseconds(10);
digitalWrite(trigerpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigerpin,LOW);
traveltime=pulseIn(echopin,HIGH);
distance=(0.0001715*traveltime);
Serial.println(traveltime);
Serial.println(distance);
delay(100);
if (distance<=(1.00))
{digitalWrite(buzpin,HIGH);
delay(100);
digitalWrite(buzpin,LOW);
delay(100);}
if (distance>1.00)
{  digitalWrite(buzpin,LOW);  }
}
