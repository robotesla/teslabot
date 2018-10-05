from serial import Serial
ser = Serial('/dev/cu.usbmodem14201') # connect to arduino tru serial port

def send(command):
	ser.write(command.encode())
	return True

def recive():
    return ser.readline()[:-2]

__all__ = ['firmware', 'system']