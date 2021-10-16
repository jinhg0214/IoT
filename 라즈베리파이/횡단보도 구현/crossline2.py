from gpiozero import Button, LED
from time import sleep

car_red = LED(17)
car_yellow = LED(27)
car_green = LED(22)

human_red = LED(9)
human_green = LED(11)

button = Button(0)

while True:
    car_red.off()
    human_green.off()
    car_green.on()
    human_red.on()
    
    if button.is_pressed:
        sleep(2)

        car_green.off()
        car_yellow.on()
        
        sleep(1)
        
        car_yellow.off()
        car_red.on()
        human_red.off()
        human_green.on()
        
        sleep(5)
        for i in range(0,3):        
            sleep(0.5)
            human_green.off()
            sleep(0.5)
            human_green.on()
        