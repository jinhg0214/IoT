from gpiozero import TonalBuzzer
from gpiozero.tones import Tone
from time import sleep

lst = [242.32, 352.34, 810.2]

b = TonalBuzzer(14)

while True:
    for i in range(3):
            
        b.play(lst[i])
        sleep(0.2)
    b.stop()
    break