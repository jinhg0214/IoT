int BOOZER = 5; // pin 3
int TRIG = 2;
int ECHO = 3;
int dis=101;

void setup() {
  pinMode(BOOZER, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  dis = (pulseIn(ECHO, HIGH) * 340 / 2) / 10000;

  Serial.println(dis);  Serial.println("cm");

  delay(100);
  
  if(0 < dis && dis < 5){
     tone(BOOZER, 523.3);
     delay(300);
     noTone(BOOZER);
     delay(300);
  }
  else if(5 <= dis && dis < 10){
     tone(BOOZER, 392.2);
     delay(500);
     noTone(BOOZER);
     delay(500);
  }
  else if (15 <= dis && dis < 20){
     tone(BOOZER, 329.6);
     delay(600);
     noTone(BOOZER);
     delay(600);
  }
  else if (25 <= dis && dis <= 30 ) {
     tone(BOOZER, 261.6);
     delay(800);
     noTone(BOOZER);
     delay(800);
  }
}
