from sense_hat import SenseHat
from time  import sleep

hat = SenseHat()

x = 1
y = 1


def update_screen():
    hat.clear()
    hat.set_pixel(x, y, 255, 0, 0)
    
# border 
def clamp(val, min_val = 0, max_val = 7):
    return min(max_val, max(min_val, val))

def move_dot(event):
    global x, y
    if event.action in ('pressed', 'held'):
        x = clamp(x + {
            'left': -1,
            'right': 1,
            }.get(event.direction, 0)
            )
        
        y = clamp(y + {
            'up': -1,
            'down': 1,
            }.get(event.direction, 0)
            )

while True:
    event = hat.stick.wait_for_event()
    move_dot(event)
    update_screen()
    






