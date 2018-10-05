from protocol import send
from protocol import recive

def get_battey():
    send('SYS BATTERY')
    return recive()

def temperature():
    send('SYS TEMPERATURE')
    return recive()

def update_sd(bytesdata):
    send('SYS UPDATE_SD ' + bytearray)
    while True:
        if recive() == 'OK':
            return True