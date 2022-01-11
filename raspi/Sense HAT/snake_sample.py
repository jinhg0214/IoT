from sense_hat import SenseHat
from time import sleep
import random

x = y = 4

bang = 'up'
hat = SenseHat()

snake = [[x,y]]
apple_x = random.randrange(1,7)
apple_y = random.randrange(1,7)

def update_screen():
    hat.clear()
    # show snake
    for i in range snake:
    hat.set_pixel(x, y, 255, 255, 255)
    
    
    # show apple
    hat.set_pixel(apple_x, apple_y, 255, 0, 0)

def clamp(value, min_value=0, max_value=7):
    return min(max_value, max(min_value, value))

def move_dot(event):
    global x, y
    global bang
    if event.action in ('pressed', 'held'):
        if event.direction == 'up': bang = 'up'
        if event.direction == 'down': bang = 'down'
        if event.direction == 'left': bang = 'left'
        if event.direction == 'right': bang = 'right'
        
def gogo():
    global x, y
    global bang
    if bang == 'up' : y -= 1
    if bang == 'down' : y += 1
    if bang == 'left' : x -= 1
    if bang == 'right' : x += 1
    
    # wall
    if y == 8 : y = 7
    if y == -1 : y = 0
    if x == 8 : x = 7
    if x == -1 : x = 0
    
    # if snake head collsion with apple
    
    

update_screen()
cnt = 0

while True:
    cnt += 1
    
    # refresh screnn when joystick input or cnt reach at 100000
    for event in hat.stick.get_events():
        move_dot(event)
        update_screen()
    
    if cnt == 100000: #tickRate
        gogo()
        cnt = 0
        update_screen()
 
