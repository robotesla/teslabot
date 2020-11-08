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
stdin, stdout, stderr = ssh.exec_command('sudo chmod o+rw /dev/ttyUSB1')
print("Please, enter this code in the bash: sudo cat -v < /dev/ttyUSB1")
# HEAD CONTROL
def stop_head():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'HEAD STOP_ACTION ' > /dev/ttyUSB1 ")
def PITCH_UP ():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'HEAD PITCH_UP 150 ' > /dev/ttyUSB1 ")
    print('\r' + "head up" + ' ' * 40, end='')
def PITCH_DOWN():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'HEAD PITCH_DOWN 150 ' > /dev/ttyUSB1 ")
    print('\r' + "head down" + ' ' * 40, end='')
def YAW_LEFT():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'HEAD YAW_LEFT 10 ' > /dev/ttyUSB1 ")
    print('\r' + "head left" + ' ' * 40, end='')
def YAW_RIGHT():
    stdin, stdout, stderr = ssh.exec_command("sudo echo -ne 'HEAD YAW_RIGHT 10 ' > /dev/ttyUSB1 ")
    print('\r' + "head right" + ' ' * 40, end='')


while 1:
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
stdin.close()