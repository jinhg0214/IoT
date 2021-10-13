#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = A0;
int sensorValue = 0;
int led = 13;

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(led,OUTPUT);

}

void loop() {

  delay(2000);
  sensorValue = analogRead(sensorPin);
  // 센서가 물밖에 있을때
  if(sensorValue < 200){
    lcd.setCursor(0,0);
    lcd.print("     EMPTY     ");
    lcd.setCursor(0,1);
    lcd.print("               ");
    digitalWrite(led,LOW);
  }

  //센서작동(저수위)
  if(sensorValue > 490){
    lcd.setCursor(0,0);
    lcd.print("  WATER LEVEL  ");
    lcd.setCursor(0,1);
    lcd.print("      LOW      ");
    digitalWrite(led,LOW);
  }

  //센서작동(중수위)
  if(sensorValue > 550){
    lcd.setCursor(0,0);
    lcd.print("  WATER LEVEL  ");
    lcd.setCursor(0,1);
    lcd.print("    MEDIUM    ");
    digitalWrite(led,LOW);
  }

//센서작동(고수위)
  if(sensorValue > 630){
    lcd.setCursor(0,0);
    lcd.print("  WATER LEVEL  ");
    lcd.setCursor(0,1);
    lcd.print("     HIGH     ");
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }

  Serial.print(sensorValue);
  Serial.println();
  delay(1000);
 

}
