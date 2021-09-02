import RPi.GPIO as GPIO
import time
from motor import AlphaBot2
from TRSensors import TRSensor

# Wheel setup
whl = AlphaBot2()
# Button setup
Button = 7
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(Button,GPIO.IN,GPIO.PUD_UP)
print("Press button to start")
# Sensor
TR = TRSensor()

while (GPIO.input(Button) != 0):
    time.sleep(0.05)
try:
    while True:
        sensors = TR.AnalogRead()
        sensor1 = sensors[0]
        sensor2 = sensors[1]
        sensor3 = sensors[2]
        sensor4 = sensors[3]
        sensor5 = sensors[4]

        if sensor1 > 150:
            #조건변경
            if sensor1 < 700 and sensor5 < 700:
                print("forward2: ")
                print(TR.AnalogRead())
                whl.forward()
            else:
                if sensor2 < 500 or sensor1 < 650:      #left
                    if sensor1 < 650:
                        print("         left1: ")
                        print(TR.AnalogRead())
                        whl.pointleft()
                    else:
                        print("             left2: ")
                        print(TR.AnalogRead())
                        whl.curveleft_2()
                elif sensor4 < 500 or sensor5 < 650:    #right
                    if sensor5 < 650:
                        print("         right1: ")
                        print(TR.AnalogRead())
                        whl.pointright()
                    else:
                        print("             right2: ")
                        print(TR.AnalogRead())
                        whl.curveright_2()
                elif sensor3 < 600:                     #forward
                    if sensor2 < 800:
                        print(" forwardright: ")
                        print(TR.AnalogRead())
                        whl.curveright()
                    elif sensor4 < 800:
                        print(" forwardleft: ")
                        print(TR.AnalogRead())
                        whl.curveleft()
                    else:
                        print("forward: ")
                        print(TR.AnalogRead())
                        whl.forward()
                else:
                    print("error: ")
                    print(TR.AnalogRead())
                    whl.forward()

except:
    print("except")
    GPIO.cleanup()