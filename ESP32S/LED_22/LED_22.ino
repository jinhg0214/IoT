#define LED_1_PIN 23
#define LED_2_PIN 22
#define LED_3_PIN 21
#define LED_4_PIN 19

#define BTN_1_PIN 12
#define BTN_2_PIN 13
#define BTN_3_PIN 9
#define BTN_4_PIN 11

#define BUZZER_PIN 18

#define VR_PIN A13

void setup() {
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);

  pinMode(BTN_1_PIN, INPUT_PULLUP);
  pinMode(BTN_2_PIN, INPUT_PULLUP);
  pinMode(BTN_3_PIN, INPUT_PULLUP);
  pinMode(BTN_4_PIN, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}

int key[4] = {0};
int led_state[4] = {0};

int vr = 0;

void loop() {

  // btn input
  key[0] = digitalRead(BTN_1_PIN);
  key[1] = digitalRead(BTN_2_PIN);
  key[2] = digitalRead(BTN_3_PIN);
  key[3] = digitalRead(BTN_4_PIN);

  // beep
  if(key[0] == 0 || key[1] == 0 || key[2] == 0 || key[3] == 0){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(20);
    digitalWrite(BUZZER_PIN, LOW);
  }

  if(key[0] == 0){
    if(led_state[0] == 0){ digitalWrite(LED_1_PIN, HIGH); led_state[0] = 1;}
    else{                  digitalWrite(LED_1_PIN, LOW);  led_state[0] = 0;}
  }
  else if(key[1] == 0){
    if(led_state[1] == 0){ digitalWrite(LED_2_PIN, HIGH); led_state[1] = 1;}
    else{                  digitalWrite(LED_2_PIN, LOW);  led_state[1] = 0;}
  }
  else if(key[2] == 0){
    if(led_state[2] == 0){ digitalWrite(LED_3_PIN, HIGH); led_state[2] = 1;}
    else{                  digitalWrite(LED_3_PIN, LOW);  led_state[2] = 0;}
  }
  else if(key[3] == 0){
    if(led_state[3] == 0){ digitalWrite(LED_4_PIN, HIGH); led_state[3] = 1;}
    else{                  digitalWrite(LED_4_PIN, LOW);  led_state[3] = 0;}
  }

  vr = analogRead(A13);
  Serial.print("[VR = "); 
  Serial.print(vr); 
  
  Serial.print("] [VCC = "); 
  float vcc = (float(vr / 4096.0) * 3.3);
  Serial.print(vcc); 

  Serial.print("] [TEMP = "); 
  float temp = (float(vr / 4096.0) * 120) - 40;
  Serial.print(temp); 
  Serial.println("]");
  
  delay(100);
}
