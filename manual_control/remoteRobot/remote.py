press = 0
press_head = 0
emerg_stop = 0
speed_motors = 120
speed_pitch = 120
speed_yaw = 120
import keyboard
import serial

# serial setup

#motors:
serMotors = serial.Serial('/dev/cu.usbserial-A901HOQC')
serMotors.baudrate = 9600
#head:
serHead = serial.Serial('/dev/cu.usbserial-A901HOQC')
serHead.baudrate = 9600

def stop_motors():
    serMotors.write("MOTORS STOP_ACTION")

    print('\r' + "stop action" + ' ' * 40, end='')
def move_up():
    serMotors.write("MOTORS MOVE_FORWARD", speed_motors)
    print('\r' + "move up" + ' ' * 40, end='')
def move_down():
    serMotors.write("MOTORS MOVE_BACKWARD", speed_motors)
    print('\r' + "move down" + ' ' * 40, end='')
def move_left():
    serMotors.write("MOTORS TURN_LEFT", speed_motors)
    print('\r' + "move left" + ' ' * 40, end='')
def move_right():
    serMotors.write("MOTORS TURN_RIGHT", speed_motors)
    print('\r' + "move right" + ' ' * 40, end='')

# HEAD CONTROL
def stop_head():
    serMotors.write("HEAD STOP_ACTION")
    print('\r' + "stop action head" + ' ' * 40, end='')
def PITCH_UP ():
    serMotors.write("HEAD PITCH_UP", speed_pitch)
    print('\r' + "head up" + ' ' * 40, end='')
def PITCH_DOWN():
    serMotors.write("HEAD PITCH_DOWN", speed_pitch)
    print('\r' + "head down" + ' ' * 40, end='')
def YAW_LEFT():
    serMotors.write("HEAD YAW_LEFT", speed_yaw)
    print('\r' + "head left" + ' ' * 40, end='')
def YAW_RIGHT():
    serMotors.write("HEAD YAW_RIGHT", speed_yaw)
    print('\r' + "head right" + ' ' * 40, end='')


while 1:
#              MOTORS CONTROL
    while keyboard.is_pressed(13):
        if press == 0:
            move_up()
        press = 1
    while keyboard.is_pressed(0):
        if press == 0:
            move_left()
        press = 1
    while keyboard.is_pressed(1):
        if press == 0:
            move_down()
        press = 1
    while keyboard.is_pressed(2):
        if press == 0:
            move_right()
        press = 1
    if press == 1:
        press = 0
        stop_motors()
#              HEAD CONTROL
    while keyboard.is_pressed(34):
        if press_head == 0:
            PITCH_UP()
        press_head = 1
    while keyboard.is_pressed(40):
        if press_head == 0:
            PITCH_DOWN()
        press_head = 1
    while keyboard.is_pressed(38):
        if press_head == 0:
            YAW_LEFT()
        press_head = 1
    while keyboard.is_pressed(37):
        if press_head == 0:
            YAW_RIGHT()
        press_head = 1
    if press_head == 1:
        press_head = 0
        stop_head()
#           !!!EMERGENCY STOP!!!
    while keyboard.is_pressed('space'):
        if emerg_stop == 0:
            stop_head()
            stop_motors()
        emerg_stop = 1
    if emerg_stop == 1:
        emerg_stop = 0
        print("EMERGENCY STOP")