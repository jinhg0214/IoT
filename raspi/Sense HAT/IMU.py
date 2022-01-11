from sense_hat import SenseHat
from time import sleep

hat = SenseHat()
hat.set_imu_config(True, True, True)

while True:
    orientation = hat.get_orientation_degrees() #pitch, roll, yaw
    print("p : {pitch}, r: {roll}, y:{yaw}".format(**orientation))
    
    raw = hat.get_compass_raw()
    
    print("x : {x}, y : {y}, z : {z}".format(**raw))
    
    north = hat.get_compass() #north degree
    print("North : %s" %north)
    
    sleep(1)