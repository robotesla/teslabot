from protocol import send
from protocol import recive

def move_forward(speed=255):
    send('MOTORS MOVE_FORWARD ' + str(speed))

def move_backward(speed=255):
    send('MOTORS MOVE_BACKWARD ' + str(speed))

def turn_left(speed=255):
    send('MOTORS TURN_LEFT ' + str(speed))

def turn_right(speed=255):
    send('MOTORS TURN_RIGHT ' + str(speed))

def get_action():
    send('MOTORS GET_ACTION')
    while True:
        output = recive()
        if output != '' or output != None:
            return output

def stop_action():
    send('MOTORS STOP_ACTION')