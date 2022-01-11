# FND + 74LS47
# 74LS47을 이용하면 더 적은 GPIO로도 FND를 출력 할 수 있다

from gpiozero import LED
from time import sleep

# 4개의 GPIO선 사용
A0 = LED(14)
A1 = LED(15)
A2 = LED(18)
A3 = LED(23)

number = 0
r = 0

#GPIO
seg = [0] * 8
seg[0] = LED(5)
seg[1] = LED(6)
seg[2] = LED(13)
seg[3] = LED(19)
seg[4] = LED(26)
seg[5] = LED(16)
seg[6] = LED(20)
seg[7] = LED(21)

digitForNum = [
    [1,1,1,1,1,1,0,0],    #0
    [0,1,1,0,0,0,0,0],    #1
    [1,1,0,1,1,0,1,0],    #2
    [1,1,1,1,0,0,1,0],    #3
    [0,1,1,0,0,1,1,0],    #4
    [1,0,1,1,0,1,1,0],    #5
    [1,0,1,1,1,1,1,0],    #6
    [1,1,1,0,0,1,0,0],    #7
    [1,1,1,1,1,1,1,0],    #8
    [1,1,1,1,0,1,1,0],    #9
        ]

try:
    while 1:

    #74LS47P
    if number//(2**3) :
        A3.on()
    else :
        A3.off()
    r = number % (2**3)
    
    if r//(2**2) :
        A2.on()
    else :
        A2.off()
    r = r % (2**2)
    
    if r//(2**1) :
        A1.on()
    else :
        A1.off()
    r = r % (2**1)
    
    if r//(2**0) :
        A0.on()
    else :
        A0.off()
    r = r % (2**0)
    
    number += 1
    sleep(0.1)
    
    if number > 9 :
        number = 0
        
    #GPIO
    for j in range(10):
                 for i in range(8):
                     if(not digitForNum[j][i]):
                         seg[i].off()  # anode타입과 cathode타입에 따라
                     else :
                         seg[i].on() # anode타입과 cathode 타입에 따라 변경
                 sleep(0.25)
    
except KeyboardInterrupt:
    pass