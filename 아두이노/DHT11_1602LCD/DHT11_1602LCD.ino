#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}
void loop() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
}
