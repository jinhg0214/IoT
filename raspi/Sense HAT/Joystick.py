from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

while True:
    event = sense.stick.wait_for_event()
    print("The joystick was {} {}". format(event.action, event.direction))
    #4 direction 
    #3 action : pressed, held, released
    sleep(0.1)
    