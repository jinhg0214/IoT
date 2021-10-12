import RPi.GPIO as GPIO 
import time 

pirPin = 7  # pir 센서는 GPIO 7
buzzerPin = 11  # 버저는 11
GPIO.setmode(GPIO.BOARD)  # GPIO.보드로 설정

GPIO.setup(pirPin, GPIO.IN); # pir는 입력
GPIO.setup(buzzerPin, GPIO.OUT); # 버저는 출력
GPIO.output(buzzerPin, GPIO.LOW) # 버저 초기 설정은 0으로

# 알람 이벤트 설정
def soundAlarm(pirPin):
  print("Sound Alarm") 
  GPIO.output(buzzerPin, GPIO.HIGH)  # 버저 키기
  time.sleep(2) # 2초간 울리고
  GPIO.output(buzzerPin, GPIO.LOW)  # 버저를 끈다

# 움직임이 감지되면 (pir센서 값이 1이라면) soundAlarm을 callback 한다.
GPIO.add_event_detect(pirPin, GPIO.RISING, callback=soundAlarm); # 첫번째 인자의 핀으로부터, 두번째 값이 발생하면, 세번째를 callback 하는 함수
# 0->1 RISING, 1->0 FALLING, BOTH

try:
  while True:

    # 여기서 계속 이벤트 감지를 하게됨.
    pass

except KeyboardInterrupt: # ctrl+C
  print("You ended the program")

finally:
  GPIO.cleanup()
© 2021 GitHub, Inc.