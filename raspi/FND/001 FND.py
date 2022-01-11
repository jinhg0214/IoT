# 버튼을 누르면 FND 전체 키는 프로그램.
# Common Anode(전체 양극) 방식 이용 -> off신호를 주면 켜진다. 

from gpiozero import LED, Button
from time import sleep

g = LED(14)
f = LED(26)
a = LED(15)
b = LED(18)

e = LED(23)
d = LED(24)
c = LED(25)
DP = LED(8)

btn = Button(16)

lst = [g, f, a, b, e, d, c, DP]

# 처음엔 모두 끈다
for i in range(8):
    lst[i].on()
    
def fnd_on():
    for i in range(8):
            lst[i].off() 

def fnd_off():
    for i in range(8):
            lst[i].on()

btn.when_pressed = fnd_on # 버튼이 눌려있는 경우에만 모든 LED를 킨다
btn.when_released = fnd_off 
    
while True:
    pass
        