from sense_hat import SenseHat
from time import sleep

sense = SenseHat()
sense.set_imu_config(True, True, True)

x = 5
y = 5
r = 255
g = 255
b = 255
roll = 0
pitch = 0
yaw = 0

def update_screen():
    sense.clear()
    sense.set_pixel(x, y, r, g, b)
    
# border 
def clamp(val, min_val = 0, max_val = 7):
    return min(max_val, max(min_val, val))

def move_dot(pitch, roll, x, y):
    new_x = x
    new_y = y
    if 1 < pitch < 179 and x != 0:
        new_x -= 1
    elif 359 > pitch > 181 and x != 7:
        new_x += 1
    if 1 < roll < 179 and y != 7:
        new_y += 1
    elif 359 > roll > 181 and y != 0:
        new_y -= 1
    
    return new_x, new_y
        
        
while True:
    
        
    # print
    # roll, pitch, yaw
    orientation = sense.get_orientation_degrees()
    pitch = orientation["pitch"]
    roll = orientation["roll"]
    yaw = orientation["yaw"]

    x,y = move_dot(pitch,roll,x,y)
    update_screen()
    
    print("p : {:.5f}, r : {:.5f} ,y : {:.5f}" .format(pitch, roll, yaw))
    
    # temp
    temp = sense.get_temperature()
    print("Temperature : {:.1f}ºC" .format(temp))
    if temp < 37:
        r = 0
        g = 0
        b = 255
    elif temp < 38 :
        r = 255
        g = 255
        b = 255
    else :
        r = 255
        g = 0
        b = 0
    #print("r : {}, g : {}, b : {}" .format(r, g, b))
    
    sleep(0.1)
