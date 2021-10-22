from sense_hat import SenseHat
from time import sleep

sense = SenseHat()
sense.set_imu_config(True, True, True)

x = 5
y = 5

def update_screen():
    sense.clear()
    sense.set_pixel(x, y, 0, 255, 255)
    
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
    #joystick event
    for event in sense.stick.get_events():
        #print("The joystick was {} {}".format(event.action, event.direction))
        
        move_dot(event)
        update_screen()
        
    # print
    # roll, pitch, yaw
    orientation = sense.get_orientation_degrees()
    print("p : {pitch:.5f}, r : {roll:.5f} ,y : {yaw:.5f}" .format(**orientation))
    
    # Pressure, Altitude
    pressure = sense.get_pressure()
    print("Pressure : {:.2f} Millibars" .format(pressure))
    
    # temp, humidiry
    humidity = sense.get_humidity()
    temp = sense.get_temperature()
    print("Temperature : {:.1f}ºC" .format(temp))
    print("Humidity : {:.0f}%" .format(humidity))
    
    sleep(0.1)