from gpiozero import Button, LED
from time import sleep

col_red = LED(17)
col_yellow = LED(27)
col_green = LED(22)

row_red = LED(10)
row_yellow = LED(9)
row_green = LED(11)

col_btn = Button(25)
row_btn = Button(14)

state = 0
add_time = 3

while True:
    # wait for btn input
    if state == 0:
        if col_btn.is_pressed:
            state = 1
        elif row_btn.is_pressed:
            state = 2
        sleep(0.1)
    # row to col transition
    elif state == 1:
        row_green.off()
        col_red.off()
        col_yellow.on()
        row_yellow.on()
        
        sleep(2)
        
        col_yellow.off()
        row_yellow.off()
        col_green.on()
        row_red.on()
  
        state = 3
    # col to row transition
    elif state == 2:
        col_green.off()
        row_red.off()
        col_yellow.on()
        row_yellow.on()
        
        sleep(2)
        
        col_yellow.off()
        row_yellow.off()
        col_red.on()
        row_green.on()
        
        state = 3
    else :
        sleep(5)
        state = 0
            
        
        
    