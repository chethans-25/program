import RPi.GPIO as g
import time as t

g.setmode(g.BOARD)
g.setup(12,g.OUT)
pwm=g.PWM(12,50)
pwm.start(0)

for i in range(10):
    pwm.ChangeDutyCycle(i)
    t.sleep(0.1)
for i in range(10,0,-1):
    pwm.ChangeDutyCycle(i)
    t.sleep(0.1)
