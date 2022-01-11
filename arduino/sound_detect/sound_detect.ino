int SensorA0=A0;

int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;
int LED5 = 7;

int SensorValue = 0;

void setup() {

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  SensorValue = analogRead(SensorA0);

  Serial.println(SensorValue);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
//  delay(1);

  if(SensorValue > 52){digitalWrite(LED1,HIGH);}
  if(SensorValue > 60){digitalWrite(LED2,HIGH);}
  if(SensorValue > 65){digitalWrite(LED3,HIGH);}
  if(SensorValue > 70){digitalWrite(LED4,HIGH);}
  if(SensorValue > 75){digitalWrite(LED5,HIGH);}

  delay(1);

}
