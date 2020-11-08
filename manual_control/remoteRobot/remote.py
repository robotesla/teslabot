press = 0
press_head = 0
emerg_stop = 0
speed_motors = 120
speed_pitch = 120
speed_yaw = 120
import keyboard
import paramiko
#ssh setup

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect('192.168.1.6', username='pi', password='1234')
stdin, stdout, stderr = ssh.exec_command('sudo bash')
stdin, stdout, stderr = ssh.exec_command('teslaN1')
stdin, stdout, stderr = ssh.exec_command('sudo chmod o+rw /dev/ttyUSB0')
print("Please, enter this code in the bash: sudo cat -v < /dev/ttyUSB0")
# serial setup
def stop_motors():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'MOTORS STOP_ACTION ' > /dev/ttyUSB0 ")
    print('\r' + "stop action" + ' ' * 40, end='')
def move_up():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'MOTORS MOVE_FORWARD 120 ' > /dev/ttyUSB0 ")
    print('\r' + "move up" + ' ' * 40, end='')
def move_down():
    print('\r' + "move down" + ' ' * 40, end='')
def move_left():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'MOTORS TURN_LEFT 120 ' > /dev/ttyUSB0 ")
    print('\r' + "move left" + ' ' * 40, end='')
def move_right():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'MOTORS TURN_RIGHT 120 ' > /dev/ttyUSB0 ")
    print('\r' + "move right" + ' ' * 40, end='')

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
stdin.close()