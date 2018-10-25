from serial import Serial
ser = Serial('/dev/cu.usbserial-1410', 9600) # connect to arduino tru serial port

def send(command):
	return ser.write((command + '\nl').encode())

def recive():
    return ser.readline()[:-2]

__all__ = ['firmware', 'system']