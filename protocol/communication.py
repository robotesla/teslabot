import serial
import serial
ser = serial.Serial('/dev/ttyUSB0') # connect to arduino tru serial port

def send(command):
	ser.write(b(command))
	return True

def recive():
	# here recive code
	# not done yet
	pass