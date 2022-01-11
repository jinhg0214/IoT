from gpiozero import DistanceSensor
from time import sleep

sensor = DistanceSensor(20, 16)

while True:
    print(sensor.distance, "m")
    sleep(0.1)