# FND를 이용해 숫자 표현하기
from gpiozero import LED
from time import sleep

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
        for j in range(10):
             for i in range(8):
                 if(not digitForNum[j][i]):
                     seg[i].on()  # anode타입과 cathode타입에 따라 변경
                 else :
                     seg[i].off() # anode타입과 cathode 타입에 따라 변경
             sleep(0.5)

except KeyboardInterrupt:
    pass